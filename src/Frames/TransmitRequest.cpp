#include "TransmitRequest.hh"

// STD headers
#include <numeric>
#include <random>

using namespace BeeCoLL;
using namespace BeeCoLL::Frames;

constexpr uint8_t FRAME_ID_OFFSET = 0;
constexpr uint8_t DEST_ADDR64_OFFSET1 = 8;
constexpr uint8_t DEST_ADDR64_OFFSET2 = 7;
constexpr uint8_t DEST_ADDR64_OFFSET3 = 6;
constexpr uint8_t DEST_ADDR64_OFFSET4 = 5;
constexpr uint8_t DEST_ADDR64_OFFSET5 = 4;
constexpr uint8_t DEST_ADDR64_OFFSET6 = 3;
constexpr uint8_t DEST_ADDR64_OFFSET7 = 2;
constexpr uint8_t DEST_ADDR64_OFFSET8 = 1;
constexpr uint8_t DEST_ADDR16_OFFSET1 = 10;
constexpr uint8_t DEST_ADDR16_OFFSET2 = 9;
constexpr uint8_t TRANSMIT_OPTIONS_OFFSET = 11;

TransmitRequest::TransmitRequest(const std::vector<uint8_t>& frame_data) : 
    Frame(FrameType::TRANSMIT_REQUEST, frame_data)
{
    SetFrameID(std::rand() % 255 + 1);
    SetDestNetworkAddr(0x000000000000FFFF);
    SetDestNetworkAddr(0xFFFE);
    std::vector<TransmitOptions> default_option;
    default_option.emplace_back(TransmitOptions::DEFAULT_USE_TO);
    SetTransmitOptions(default_option);
}

TransmitRequest::TransmitRequest(const Frame& other) : 
    Frame(other)
{

}

TransmitRequest::~TransmitRequest()
{

}

uint8_t
TransmitRequest::GetFrameID()
{
    return GetDataByte(FRAME_ID_OFFSET);
}

void
TransmitRequest::SetFrameID(uint8_t frame_id)
{
    SetDataByte(FRAME_ID_OFFSET, frame_id);
}

uint64_t
TransmitRequest::GetDestUniqueAddr()
{
    uint64_t addr = GetDataByte(DEST_ADDR64_OFFSET1);
    addr |= GetDataByte(DEST_ADDR64_OFFSET2) << 8;
    addr |= GetDataByte(DEST_ADDR64_OFFSET3) << 16;
    addr |= GetDataByte(DEST_ADDR64_OFFSET4) << 24;
    addr |= static_cast<uint64_t>(GetDataByte(DEST_ADDR64_OFFSET5)) << 32;
    addr |= static_cast<uint64_t>(GetDataByte(DEST_ADDR64_OFFSET6)) << 40;
    addr |= static_cast<uint64_t>(GetDataByte(DEST_ADDR64_OFFSET7)) << 48;
    addr |= static_cast<uint64_t>(GetDataByte(DEST_ADDR64_OFFSET8)) << 56;
    return addr;
}

void
TransmitRequest::SetDestUniqueAddr(const uint64_t& addr)
{
    SetDataByte(DEST_ADDR64_OFFSET1, addr);
    SetDataByte(DEST_ADDR64_OFFSET2, addr >> 8);
    SetDataByte(DEST_ADDR64_OFFSET3, addr >> 16);
    SetDataByte(DEST_ADDR64_OFFSET4, addr >> 24);
    SetDataByte(DEST_ADDR64_OFFSET5, addr >> 32);
    SetDataByte(DEST_ADDR64_OFFSET6, addr >> 40);
    SetDataByte(DEST_ADDR64_OFFSET7, addr >> 48);
    SetDataByte(DEST_ADDR64_OFFSET8, addr >> 56);
    if (addr != 0xFFFFFFFFFFFFFFFF)
    {
        SetDestNetworkAddr(0xFFFE);
    }
}

uint16_t
TransmitRequest::GetDestNetworkAddr()
{
    uint16_t addr = GetDataByte(DEST_ADDR16_OFFSET1);
    addr |= GetDataByte(DEST_ADDR16_OFFSET2) << 8;
    return addr;
}

void
TransmitRequest::SetDestNetworkAddr(uint16_t addr)
{
    SetDataByte(DEST_ADDR16_OFFSET1, addr);
    SetDataByte(DEST_ADDR16_OFFSET2, addr >> 8);
    if (addr != 0xFFFE)
    {
        SetDestUniqueAddr(0xFFFFFFFFFFFFFFFF);
    }
}

std::vector<TransmitOptions>
TransmitRequest::GetTransmitOptions()
{
    uint8_t byte = GetDataByte(TRANSMIT_OPTIONS_OFFSET);
    std::vector<TransmitOptions> v;

    // TODO replace to switch case
    if (GetDataBitMask(byte, TransmitOptions::DISABLE_ACK))
    {
        v.push_back(TransmitOptions::DISABLE_ACK);
    }
    if (GetDataBitMask(byte, TransmitOptions::INDIRECT_TRANSMISSION))
    {
        v.push_back(TransmitOptions::INDIRECT_TRANSMISSION);
    }
    if (GetDataBitMask(byte, TransmitOptions::MULTICAST))
    {
        v.push_back(TransmitOptions::MULTICAST);
    }
    if (GetDataBitMask(byte, TransmitOptions::SECURE_SESSION_ENCRYPTION))
    {
        v.push_back(TransmitOptions::SECURE_SESSION_ENCRYPTION);
    }
    if (GetDataBitMask(byte, TransmitOptions::ENABLE_APS_ENCRYPTION))
    {
        v.push_back(TransmitOptions::ENABLE_APS_ENCRYPTION);
    }
    if (GetDataBitMask(byte, TransmitOptions::USE_EXTENDED_TIMEOUT))
    {
        v.push_back(TransmitOptions::USE_EXTENDED_TIMEOUT);
    }

    return v;
}

void
TransmitRequest::SetTransmitOptions(const std::vector<TransmitOptions>& options)
{
    uint8_t byte = std::accumulate(options.begin(), options.end(), 0);
    SetDataByte(TRANSMIT_OPTIONS_OFFSET, byte);
}

std::vector<uint8_t>
TransmitRequest::GetPayload()
{
    std::vector<uint8_t> payload = GetData();
    payload.erase(payload.begin(), payload.begin() + 11);
    return payload;
}

void
TransmitRequest::SetPayload(const std::vector<uint8_t>& payload)
{
    InsertDataAT(14, payload);
}
