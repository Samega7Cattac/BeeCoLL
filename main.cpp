#include <iostream>

#include "Nodes/Coordinator.hh"

#include "Frames/ExplicitRxIndicator.hh"
#include "Frames/TransmitRequest.hh"
#include "Frames/RecievePacket.hh"

#include "ATCommands/ND.hh"

#include <iomanip>

void HandleNodes(const BeeCoLL::Frame& frame)
{
    if (frame.GetFrameType() == BeeCoLL::Frames::EXPLICIT_RX_INDICATOR_FRAME_ID)
    {
        BeeCoLL::Frames::ExplicitRxIndicator reply_frame(frame);
        std::cout << "RECV: " << std::hex << reply_frame.GetSourceUniqueAddr() << std::dec << " | " << reply_frame.GetReceivedDataToString() << std::endl;
    }
    else if (frame.GetFrameType() == BeeCoLL::Frames::RECEIVE_PACKET_FRAME_ID)
    {
        BeeCoLL::Frames::RecievePacket reply_frame(frame);
        std::vector<uint8_t> data = reply_frame.GetReceivedData();
        uint8_t sensor_id = data[0];
        if (sensor_id == 1)
        {
            if (data.size() != 13)
            {
                std::cout << std::setprecision(6) << sensor_id << " sensor data size wrong" << std::endl;
            }
            std::cout << "[SCD40]" << std::endl;
            uint32_t co2;
            co2 = data[1];
            co2 |= static_cast<uint16_t>(data[2]) << 8;
            co2 |= static_cast<uint32_t>(data[3]) << 16;
            co2 |= static_cast<uint32_t>(data[4]) << 24;
            std::cout << "\tCo2: " << std::fixed << std::setprecision(6) << std::bit_cast<float>(co2) << std::endl;
            uint32_t temp;
            temp = data[5];
            temp |= static_cast<uint16_t>(data[6]) << 8;
            temp |= static_cast<uint32_t>(data[7]) << 16;
            temp |= static_cast<uint32_t>(data[8]) << 24;
            std::cout << "\tTemperature: " << std::fixed << std::setprecision(6) << std::bit_cast<float>(temp) << std::endl;
            uint32_t humidity;
            humidity = data[9];
            humidity |= static_cast<uint16_t>(data[10]) << 8;
            humidity |= static_cast<uint32_t>(data[11]) << 16;
            humidity |= static_cast<uint32_t>(data[12]) << 24;
            std::cout << "\tHumidity: " << std::fixed << std::setprecision(6) << std::bit_cast<float>(humidity) << std::endl;
        }
        else if (sensor_id == 2)
        {
            if (data.size() != 3)
            {
                std::cout << sensor_id << " sensor data size wrong" << std::endl;
            }
            std::cout << "[VOC]" << std::endl;
            uint16_t voc;
            voc = data[1];
            voc |= static_cast<uint16_t>(data[2]) << 8;
            std::cout << "\tSRAW_VOC: " << voc << std::endl;
        }
        else if (sensor_id == 3)
        {
            if (data.size() != 21)
            {
                std::cout << sensor_id << " sensor data size wrong" << std::endl;
            }
            std::cout << "[Modbus]" << std::endl;
            uint32_t voltage;
            voltage = data[1];
            voltage |= static_cast<uint16_t>(data[2]) << 8;
            voltage |= static_cast<uint32_t>(data[3]) << 16;
            voltage |= static_cast<uint32_t>(data[4]) << 24;
            std::cout << "\tVoltage: " << std::fixed << voltage << std::endl;
            uint32_t current;
            current = data[5];
            current |= static_cast<uint16_t>(data[6]) << 8;
            current |= static_cast<uint32_t>(data[7]) << 16;
            current |= static_cast<uint32_t>(data[8]) << 24;
            std::cout << "\tCurrent: " << std::fixed << current << std::endl;
            uint32_t power;
            power = data[9];
            power |= static_cast<uint16_t>(data[10]) << 8;
            power |= static_cast<uint32_t>(data[11]) << 16;
            power |= static_cast<uint32_t>(data[12]) << 24;
            std::cout << "\tPower: " << std::fixed << power << std::endl;
            uint32_t kvarh;
            kvarh = data[13];
            kvarh |= static_cast<uint16_t>(data[14]) << 8;
            kvarh |= static_cast<uint32_t>(data[15]) << 16;
            kvarh |= static_cast<uint32_t>(data[16]) << 24;
            std::cout << "\tKvar/h: " << std::fixed << kvarh << std::endl;
            uint32_t kwh;
            kwh = data[17];
            kwh |= static_cast<uint16_t>(data[18]) << 8;
            kwh |= static_cast<uint32_t>(data[19]) << 16;
            kwh |= static_cast<uint32_t>(data[20]) << 24;
            std::cout << "\tKw/h: " << std::fixed << kwh << std::endl;
        }
        else if (sensor_id == 4)
        {
            if (data.size() != 5)
            {
                std::cout << sensor_id << " sensor data size wrong" << std::endl;
            }
            std::cout << "[LUX]" << std::endl;
            uint32_t co2;
            co2 = data[1];
            co2 |= static_cast<uint16_t>(data[2]) << 8;
            co2 |= static_cast<uint32_t>(data[3]) << 16;
            co2 |= static_cast<uint32_t>(data[4]) << 24;
            std::cout << "\tLux: " << std::fixed << std::setprecision(6) << std::bit_cast<float>(co2) << std::endl;
        }
    }
}

int main()
{
    // Creates an instance of a coordinator device
    BeeCoLL::Coordinator zigbee("/dev/ttyUSB0");

    // Starts the discover process of nodes in the network
    zigbee.StartDiscover();
    // Gets a list of all nodes in the network
    std::vector<std::shared_ptr<BeeCoLL::NetworkNode>> nodes = zigbee.GetNetworkNodes();

    for (std::shared_ptr<BeeCoLL::NetworkNode> node : nodes)
    {
        // Sets the callback that will be triggered when receiving data from the node
        // void (const BeeCoLL::Frame&)
        node->SetCallback(&HandleNodes);

        // Send a message with a '1' char
        std::vector<uint8_t> msg = { '1' };
        zigbee.SendMessageToNode(node->GetUniqueAddress(), msg);
    }
    
    getchar();
    return 0;
}