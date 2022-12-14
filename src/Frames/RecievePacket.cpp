#include "RecievePacket.hh"

//STD headers
#include <algorithm>

constexpr uint8_t SOURCE_ADDR64_OFFSET1 = 7;
constexpr uint8_t SOURCE_ADDR64_OFFSET2 = 6;
constexpr uint8_t SOURCE_ADDR64_OFFSET3 = 5;
constexpr uint8_t SOURCE_ADDR64_OFFSET4 = 4;
constexpr uint8_t SOURCE_ADDR64_OFFSET5 = 3;
constexpr uint8_t SOURCE_ADDR64_OFFSET6 = 2;
constexpr uint8_t SOURCE_ADDR64_OFFSET7 = 1;
constexpr uint8_t SOURCE_ADDR64_OFFSET8 = 0;
constexpr uint8_t SOURCE_NETWORK_ADDR16_OFFSET1 = 9;
constexpr uint8_t SOURCE_NETWORK_ADDR16_OFFSET2 = 8;
constexpr uint8_t RECEIVE_OPTIONS_OFFSET = 9;
constexpr uint8_t RECEIVED_DATA_OFFSET = 10;

BeeCoLL::Frames::RecievePacket::RecievePacket(const std::vector<uint8_t>& frame_data) : 
    Frame(RECEIVE_PACKET_FRAME_ID, frame_data)
{

}

BeeCoLL::Frames::RecievePacket::RecievePacket(const Frame& other) : 
    Frame(other)
{

}

BeeCoLL::Frames::RecievePacket::~RecievePacket()
{

}

uint64_t
BeeCoLL::Frames::RecievePacket::GetSourceUniqueAddr()
{
    uint64_t addr = GetDataByte(SOURCE_ADDR64_OFFSET1);
    addr |= GetDataByte(SOURCE_ADDR64_OFFSET2) << 8;
    addr |= GetDataByte(SOURCE_ADDR64_OFFSET3) << 16;
    addr |= GetDataByte(SOURCE_ADDR64_OFFSET4) << 24;
    addr |= static_cast<uint64_t>(GetDataByte(SOURCE_ADDR64_OFFSET5)) << 32;
    addr |= static_cast<uint64_t>(GetDataByte(SOURCE_ADDR64_OFFSET6)) << 40;
    addr |= static_cast<uint64_t>(GetDataByte(SOURCE_ADDR64_OFFSET7)) << 48;
    addr |= static_cast<uint64_t>(GetDataByte(SOURCE_ADDR64_OFFSET8)) << 56;
    return addr;
}

uint16_t
BeeCoLL::Frames::RecievePacket::GetSourceNetworkAddr()
{
    uint16_t addr = GetDataByte(SOURCE_NETWORK_ADDR16_OFFSET1);
    addr |= GetDataByte(SOURCE_NETWORK_ADDR16_OFFSET2);
    return addr;
}

std::vector<BeeCoLL::Frames::ReceiveOptions>
BeeCoLL::Frames::RecievePacket::GetReceiveOptions()
{
    unsigned char byte = GetDataByte(RECEIVE_OPTIONS_OFFSET);
    std::vector<ReceiveOptions> v;
    
    if (GetDataBitMask(byte, ReceiveOptions::PACKAGE_ACK))
    {
        v.push_back(ReceiveOptions::PACKAGE_ACK);
    }
    else if (GetDataBitMask(byte, ReceiveOptions::PACKAGE_BROADCAST))
    {
        v.push_back(ReceiveOptions::PACKAGE_BROADCAST);
    }
    else if (GetDataBitMask(byte, ReceiveOptions::PACKAGE_ENCRYPTED_APS))
    {
        v.push_back(ReceiveOptions::PACKAGE_ENCRYPTED_APS);
    }
    else if (GetDataBitMask(byte, ReceiveOptions::PACKAGE_EXTENDED_TIMEOUT))
    {
        v.push_back(ReceiveOptions::PACKAGE_EXTENDED_TIMEOUT);
    }
    return v;
}

std::vector<uint8_t>
BeeCoLL::Frames::RecievePacket::GetReceivedData()
{
    std::vector<uint8_t> data = GetData();
    data.erase(data.begin(), data.begin() + RECEIVED_DATA_OFFSET + 1);
    return data;
}

std::string
BeeCoLL::Frames::RecievePacket::GetReceivedDataToString()
{
    std::vector<uint8_t> data = GetReceivedData();
    std::string data_str;
    data_str.resize(data.size());
    std::transform(data.begin(), data.end(), data_str.begin(), [](uint8_t byte){ return static_cast<char>(byte); });
    return data_str;
}
