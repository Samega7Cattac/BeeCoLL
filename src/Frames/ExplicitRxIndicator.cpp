#include "ExplicitRxIndicator.hh"

//STD headers
#include <algorithm>

// TODO: DEBUG only
#include <iostream>

constexpr unsigned char SOURCE_ADDR64_OFFSET1 = 7;
constexpr unsigned char SOURCE_ADDR64_OFFSET2 = 6;
constexpr unsigned char SOURCE_ADDR64_OFFSET3 = 5;
constexpr unsigned char SOURCE_ADDR64_OFFSET4 = 4;
constexpr unsigned char SOURCE_ADDR64_OFFSET5 = 3;
constexpr unsigned char SOURCE_ADDR64_OFFSET6 = 2;
constexpr unsigned char SOURCE_ADDR64_OFFSET7 = 1;
constexpr unsigned char SOURCE_ADDR64_OFFSET8 = 0;
constexpr unsigned char SOURCE_NETWORK_ADDR16_OFFSET1 = 9;
constexpr unsigned char SOURCE_NETWORK_ADDR16_OFFSET2 = 8;
constexpr unsigned char SOURCE_ENDPOINT_OFFSET = 10;
constexpr unsigned char DEST_ENDPOINT_OFFSET = 11;
constexpr unsigned char CLUSTER_ID_OFFSET1 = 13;
constexpr unsigned char CLUSTER_ID_OFFSET2 = 12;
constexpr unsigned char PROFILE_ID_OFFSET1 = 15;
constexpr unsigned char PROFILE_ID_OFFSET2 = 14;
constexpr unsigned char RECEIVE_OPTIONS_OFFSET = 16;

using namespace BeeCoLL;
using namespace BeeCoLL::Frames;


ExplicitRxIndicator::ExplicitRxIndicator(const std::vector<uint8_t>& frame_data) : 
    Frame(FrameType::EXPLICIT_RX_INDICATOR, frame_data)
{

}

ExplicitRxIndicator::ExplicitRxIndicator(const Frame& other) : 
    Frame(other)
{

}

ExplicitRxIndicator::~ExplicitRxIndicator()
{

}

uint64_t
ExplicitRxIndicator::GetSourceUniqueAddr()
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
ExplicitRxIndicator::GetSourceNetworkAddr()
{
    uint16_t addr = GetDataByte(SOURCE_NETWORK_ADDR16_OFFSET1);
    addr |= GetDataByte(SOURCE_NETWORK_ADDR16_OFFSET2);
    return addr;
}

uint8_t
ExplicitRxIndicator::GetSourceEndpoint()
{
    return GetDataByte(SOURCE_ENDPOINT_OFFSET);
}

uint8_t
ExplicitRxIndicator::GetDestEndpoint()
{
    return GetDataByte(DEST_ENDPOINT_OFFSET);
}

uint16_t
ExplicitRxIndicator::GetClusterID()
{
    uint16_t id = GetDataByte(CLUSTER_ID_OFFSET1);
    id |= GetDataByte(CLUSTER_ID_OFFSET2) << 8;
    return id;
}

uint16_t
ExplicitRxIndicator::GetProfileID()
{
    uint16_t id = GetDataByte(PROFILE_ID_OFFSET1);
    id |= GetDataByte(PROFILE_ID_OFFSET2) << 8;
    return id;
}

std::vector<ReceiveOptions>
ExplicitRxIndicator::GetReceiveOptions()
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
ExplicitRxIndicator::GetReceivedData()
{
    std::vector<uint8_t> data = GetData();
    data.erase(data.begin(), data.begin() + 11);
    return data;
}

std::string
ExplicitRxIndicator::GetReceivedDataToString()
{
    std::vector<uint8_t> data = GetReceivedData();
    std::string data_str;
    data_str.resize(data.size());
    std::transform(data.begin(), data.end(), data_str.begin(), [](uint8_t byte){ return static_cast<char>(byte); });
    return data_str;
}
