#include "Coordinator.hh"
#include "Frames/ExtendedTransmitStatus.hh"
#include "Frames/ExplicitRxIndicator.hh"
#include "Frames/LocalATCommandRequest.hh"
#include "Frames/LocalATCommandResponse.hh"

#include "ATCommands/ND.hh"
#include "ATCommands/NT.hh"

// STD headers
#include <cstring>

// Linux headers
#include <fcntl.h>
#include <termios.h>

// DEBUG HEADERS
#include <iostream>

using namespace BeeCoLL;

Coordinator::Coordinator(const std::string& serial_device_path) :
    SerialInterface(serial_device_path)
{
    // Frames::LocalATCommandRequest ask_info;
    // ask_info.
}

Coordinator::~Coordinator()
{
    
}

void
Coordinator::SendAPICommand(FrameType function, const std::vector<uint8_t>& data)
{
    Frame frame(function, data);
    SendAPICommand(frame);
}

void
Coordinator::SendAPICommand(const Frame& frame)
{
    std::vector<uint8_t> data = frame.GetFrame();
    WriteToSerial(data);

    Frames::ExtendedTransmitStatus reply(ReceiveAPICommand());
    if (data[4] != 0)
    {
        if (reply.GetDeliveryStatus() != Frames::DeliveryStatus::SUCCESS)
        {
            std::cout << "CANT" << std::endl;
            // TODO: throw something
        }
    }
}

Frame
Coordinator::ReceiveAPICommand()
{
    std::vector<uint8_t> frame_data;

    frame_data = ReadFromSerial(1);

    if (frame_data[0] == START_DELIMITER)
    {
        std::vector<uint8_t> read_tmp = ReadFromSerial(2);
        frame_data.insert(frame_data.end(), read_tmp.begin(), read_tmp.end());

        unsigned int frame_size = reinterpret_cast<unsigned char>(frame_data[2]);
        frame_size |= reinterpret_cast<unsigned char>(frame_data[1]) << 8;
        ++frame_size;

        read_tmp = ReadFromSerial(frame_size);
        frame_data.insert(frame_data.end(), read_tmp.begin(), read_tmp.end());

        frame_size += 3;
        
    }
    else
    {
        // TODO: throw something
        std::cout << "delimiter not found: " << std::strerror(errno) << std::endl;
    }

    Frame frame(frame_data);

    // if (str[3] == FrameType::TRANSMIT_STATUS)
    // {
    //     return std::make_shared<Frames::ExtendedTransmitStatus>(frame);
    // }
    // else if (str[3] == FrameType::EXPLICIT_RX_INDICATOR)
    // {
    //     return std::make_shared<Frames::ExplicitRxIndicator>(frame);
    // }
    // else if (str[3] == FrameType::AT_COMMAND_RESPONSE)
    // {
    //     return std::make_shared<Frames::LocalATCommandResponse>(frame);
    // }

    return frame;
}

void
Coordinator::StartDiscover()
{
    Frames::LocalATCommandRequest at_cmd_frame;
    BeeCoLL::ATCommands::NT at_nt;
    at_cmd_frame.SetATCommand(at_nt);

    WriteToSerial(at_cmd_frame.GetFrame());
    Frames::LocalATCommandResponse at_reply_frame(ReceiveAPICommand());

    if (at_reply_frame.GetStatus() != Frames::CommandStatus::OK)
    {
        std::cout << "CANT " << std::endl;
        // TODO: throw something
    }

    BeeCoLL::ATCommands::ND at_nd;
    at_cmd_frame.SetATCommand(at_nd);

    WriteToSerial(at_cmd_frame.GetFrame());
}
