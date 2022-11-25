#include "Coordinator.hh"
#include "../Frames/ExtendedTransmitStatus.hh"
#include "../Frames/ExplicitRxIndicator.hh"
#include "../Frames/LocalATCommandRequest.hh"
#include "../Frames/LocalATCommandResponse.hh"
#include "../Frames/ExplicitRxIndicator.hh"

#include "../ATCommands/NT.hh"
#include "../ATCommands/SL.hh"
#include "../ATCommands/SH.hh"

// STD headers
#include <cstring>

// Linux headers
#include <fcntl.h>
#include <termios.h>
#include <sys/eventfd.h>

// DEBUG HEADERS
#include <iostream>

BeeCoLL::Coordinator::Coordinator(const std::string& serial_device_path) :
    SerialInterface(serial_device_path)
{
    // SetTimeoutSinceRead(30);
    SetSignalChars(false);
    SetBitsInByte(8);
    SetStopBits(false);
    SetInputBaudRate(B9600);
    SetOutputBaudRate(B9600);
    // SetControlFlow(true);
    SetSoftwareFlowControl(false);
    SetParityBit(false);
    // SetModemLine(false);
    SetOutputSpecialChars(false);
    SetInputSpecialChars(false);
    // SetCanonicalMode(false);
    SetCanonicalMode(false);
    SetEcho(false);
    SetInputSpecialChars(false);
    SetHandOnLastCall(false);
    LockFD(GetSerialFD());

    m_fd_write = eventfd(0, 0);
    m_fd_write_wait = eventfd(1, 0);
    m_fd_terminus = eventfd(0, 0);

    m_run_serial_handler = true;
    std::thread tmp_thread(&Coordinator::InterfaceHandler, this);
    m_serial_thread = std::move(tmp_thread);

    Frames::LocalATCommandRequest ask_sl;
    ATCommands::SL at_sl;
    ask_sl.SetATCommand(at_sl);

    SendAPICommand(ask_sl, std::bind(&Coordinator::ATResponseHandler, this, std::placeholders::_1));

    Frames::LocalATCommandRequest ask_sh;
    ATCommands::SH at_sh;
    ask_sh.SetATCommand(at_sh);

    SendAPICommand(ask_sh, std::bind(&Coordinator::ATResponseHandler, this, std::placeholders::_1));
}

BeeCoLL::Coordinator::~Coordinator()
{
    close(m_fd_write);
    uint64_t terminus_value = 1;
    write(m_fd_terminus, &terminus_value, sizeof(terminus_value));
    close(m_fd_terminus);
}

void
BeeCoLL::Coordinator::SendAPICommand(const Frame& frame,
                            const std::function<void(const Frame&)>& callback_function)
{
    uint64_t value;
    read(m_fd_write_wait, &value, sizeof(uint64_t));
    m_ipc_msg = frame.GetFrame();
    for (uint8_t repsonse_type : frame.GetResponseTypes())
    {
        RegisterCallback(frame.GetID(), repsonse_type, callback_function);
    }
    uint64_t event_value = 1;
    write(m_fd_write, &event_value, sizeof(event_value));
}
std::vector<std::shared_ptr<BeeCoLL::NetworkNode>>
BeeCoLL::Coordinator::GetNetworkNodes()
{
    return m_network_nodes;
}

void
BeeCoLL::Coordinator::StartDiscover()
{
    Frames::LocalATCommandRequest at_nt_frame;
    BeeCoLL::ATCommands::NT at_nt;
    at_nt_frame.SetATCommand(at_nt);

    SendAPICommand(at_nt_frame, [](const Frame& frame){
        Frames::LocalATCommandResponse at_reply_frame(frame);

        if (at_reply_frame.GetStatus() != Frames::CommandStatus::OK)
        {
            std::cout << "CANT " << std::endl;
            // TODO: throw something
        }
    });

    Frames::LocalATCommandRequest at_nd_frame;
    BeeCoLL::ATCommands::ND at_nd;
    at_nd_frame.SetATCommand(at_nd);

    SendAPICommand(at_nd_frame, std::bind(&Coordinator::ATResponseHandler, this, std::placeholders::_1));
    sleep(3);
}

void
BeeCoLL::Coordinator::RegisterCallback(uint8_t frame_id,
                              uint8_t frame_response_type,
                              std::function<void(const Frame&)> callback_function)
{
    m_callbacks.emplace_back(frame_id, frame_response_type, callback_function);
}

void
BeeCoLL::Coordinator::InterfaceHandler()
{
    unsigned int max_fd = m_fd_terminus;
    if (GetSerialFD() > max_fd)
    {
        max_fd = GetSerialFD();
    }
    if (m_fd_write > max_fd)
    {
        max_fd = m_fd_write;
    }

    fd_set read_fds;
    while(m_run_serial_handler == true)
    {
        FD_ZERO(&read_fds);
        FD_SET(m_fd_terminus, &read_fds);
        FD_SET(m_fd_write, &read_fds);
        FD_SET(GetSerialFD(), &read_fds);
        int available = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (available == -1)
        {
            // TODO: should throw on warning?
            std::cout << "select failed" << std::endl;
            continue;
        }
        else if (FD_ISSET(GetSerialFD(), &read_fds))
        {
            std::vector<uint8_t> data;
            do
            {
                data = ReadFromSerial(1);
            }while(data[0] != START_DELIMITER);

            if (data[0] == START_DELIMITER)
            {
                std::vector<uint8_t> read_tmp = ReadFromSerial(2);
                data.insert(data.end(), read_tmp.begin(), read_tmp.end());

                unsigned int frame_size = reinterpret_cast<unsigned char>(data[2]);
                frame_size |= reinterpret_cast<unsigned char>(data[1]) << 8;
                ++frame_size;

                read_tmp = ReadFromSerial(frame_size);
                data.insert(data.end(), read_tmp.begin(), read_tmp.end());
            }
            else
            {
                // TODO: throw something
                std::cout << "delimiter not found: " << std::strerror(errno) << std::endl;
            }
            Frame frame(data);
            Parser(frame);
        }
        else if (FD_ISSET(m_fd_write, &read_fds))
        {
            uint64_t event_value;
            read(m_fd_write, &event_value, sizeof(event_value));

            WriteToSerial(m_ipc_msg);
            uint64_t value = 1;
            write(m_fd_write_wait, &value, sizeof(uint64_t));
        }
        else if (FD_ISSET(m_fd_terminus, &read_fds))
        {
            m_run_serial_handler = false;
        }
    }
}

void
BeeCoLL::Coordinator::Parser(const Frame& frame)
{
    if (frame.GetType() == FrameType::EXPLICIT_RX_INDICATOR)
    {
        Frames::ExplicitRxIndicator recv_reply(frame);
        uint64_t node_addr = recv_reply.GetSourceUniqueAddr();
        for (std::shared_ptr<NetworkNode> node : m_network_nodes)
        {
            uint64_t node_uaddr = node->GetUniqueAddress();
            if (node->GetUniqueAddress() == node_addr)
            {
                node->TriggerCallback(frame);
                return;
            }
        }
    }
    uint8_t frame_id = frame.GetFrame()[4];
    for (CallbackRegister& callback : m_callbacks)
    {
        if (callback.frame_id == frame_id &&
            callback.frame_response_type == frame.GetType())
        {
            callback.callback_function(frame);
            return;
        }
    }
}

void
BeeCoLL::Coordinator::ATResponseHandler(const Frame& frame)
{
    if (frame.GetType() == FrameType::AT_COMMAND_RESPONSE)
    {
        Frames::LocalATCommandResponse at_reply(frame);
        ATCommand at_cmd = at_reply.GetATCommand();
        if (at_cmd.GetATCommand() == ND_ATCOMMAND_CODE)
        {
            ATCommands::ND at_nd(at_cmd);
            AddNode(at_nd);
        }
        else if (at_cmd.GetATCommand() == SL_ATCOMMAND_CODE)
        {
            ATCommands::SL at_sl(at_cmd);
            std::vector<uint8_t> sl_value = at_sl.GetValue();
            if (sl_value.size() != 4)
            {
                // TODO: throw something
                std::cout << "Invalid SL value" << std::endl;
            }
            uint64_t unique_addr = GetUniqueAddress();
            unique_addr |= sl_value[3];
            unique_addr |= static_cast<uint16_t>(sl_value[2]) << 8;
            unique_addr |= static_cast<uint32_t>(sl_value[1]) << 16;
            unique_addr |= static_cast<uint32_t>(sl_value[0]) << 24;
            SetUniqueAddress(unique_addr);
        }
        else if (at_cmd.GetATCommand() == SH_ATCOMMAND_CODE)
        {
            ATCommands::SH at_sh(at_cmd);
            std::vector<uint8_t> sh_value = at_sh.GetValue();
            if (sh_value.size() != 4)
            {
                // TODO: throw something
                std::cout << "Invalid SH value" << std::endl;
            }
            uint64_t unique_addr = GetUniqueAddress();
            unique_addr |= static_cast<uint64_t>(sh_value[3]) << 32;
            unique_addr |= static_cast<uint64_t>(sh_value[2]) << 40;
            unique_addr |= static_cast<uint64_t>(sh_value[1]) << 48;
            unique_addr |= static_cast<uint64_t>(sh_value[0]) << 56;
            SetUniqueAddress(unique_addr);
        }
    }
}

void
BeeCoLL::Coordinator::AddNode(ATCommands::ND& node_info)
{
    NetworkNodeInfo node;
    // node.digi_device_type = node_info.GetDigiDeviceType();
    node.manufacture_id = node_info.GetManufactureID();
    node.MY = node_info.GetMY();
    node.NI = node_info.GetNI();
    node.node_type = node_info.GetDeviceType();
    node.parent_network_addr = node_info.GetParentNetworkAddr();
    node.profile_id = node_info.GetProfileID();
    // node.rssi_of_last_hop = node_info.GetRssiOfLastHop();
    node.SH = node_info.GetSH();
    node.SL = node_info.GetSL();
    node.status = node_info.GetStatus();
    NetworkNode node_build(node, this);
    m_network_nodes.emplace_back(std::make_shared<NetworkNode>(node_build));
}
