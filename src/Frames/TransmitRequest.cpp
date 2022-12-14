#include "TransmitRequest.hh"
#include "RecievePacket.hh"
#include "ExtendedTransmitStatus.hh"

// STD headers
#include <numeric>
#include <random>

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
constexpr uint8_t BROADCAST_RADIUS_OFFSET = 11;
constexpr uint8_t TRANSMIT_OPTIONS_OFFSET = 12;

static uint8_t frame_id = 1;

BeeCoLL::Frames::TransmitRequest::TransmitRequest(const std::vector<uint8_t>& frame_data) : 
    Frame(TRANSMIT_REQUEST_FRAME_ID, frame_data)
{
    SetFrameID(frame_id++);
    SetDestNetworkAddr(0x000000000000FFFF);
    SetDestNetworkAddr(0xFFFE);
    std::vector<TransmitOptions> default_option;
    default_option.emplace_back(TransmitOptions::DEFAULT_USE_TO);
    SetTransmitOptions(default_option);
    SetBroadCastRadius(0);
    SetResponseTypes({EXPLICIT_RX_INDICATOR_FRAME_ID, RECEIVE_PACKET_FRAME_ID});
    SetStatusResponseFrameType(TRANSMIT_STATUS_FRAME_ID);
}

BeeCoLL::Frames::TransmitRequest::TransmitRequest(const Frame& other) : 
    Frame(other)
{

}

BeeCoLL::Frames::TransmitRequest::~TransmitRequest()
{

}

uint8_t
BeeCoLL::Frames::TransmitRequest::GetFrameID()
{
    return GetDataByte(FRAME_ID_OFFSET);
}

void
BeeCoLL::Frames::TransmitRequest::SetFrameID(uint8_t frame_id)
{
    SetID(frame_id);
    SetDataByte(FRAME_ID_OFFSET, frame_id);
    if (frame_id == 0)
    {
        SetStatusResponseFrameType(0);
    }
    else
    {
        SetStatusResponseFrameType(TRANSMIT_STATUS_FRAME_ID);
    }
}

uint64_t
BeeCoLL::Frames::TransmitRequest::GetDestUniqueAddr()
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
BeeCoLL::Frames::TransmitRequest::SetDestUniqueAddr(const uint64_t& addr)
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
BeeCoLL::Frames::TransmitRequest::GetDestNetworkAddr()
{
    uint16_t addr = GetDataByte(DEST_ADDR16_OFFSET1);
    addr |= GetDataByte(DEST_ADDR16_OFFSET2) << 8;
    return addr;
}

void
BeeCoLL::Frames::TransmitRequest::SetDestNetworkAddr(uint16_t addr)
{
    SetDataByte(DEST_ADDR16_OFFSET1, addr);
    SetDataByte(DEST_ADDR16_OFFSET2, addr >> 8);
    if (addr != 0xFFFE)
    {
        SetDestUniqueAddr(0xFFFFFFFFFFFFFFFF);
    }
}

uint8_t
BeeCoLL::Frames::TransmitRequest::GetBroadcastRadius()
{
    return GetDataByte(BROADCAST_RADIUS_OFFSET);
}

void
BeeCoLL::Frames::TransmitRequest::SetBroadCastRadius(uint8_t radius)
{
    SetDataByte(BROADCAST_RADIUS_OFFSET, radius);
}

std::vector<BeeCoLL::Frames::TransmitOptions>
BeeCoLL::Frames::TransmitRequest::GetTransmitOptions()
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
BeeCoLL::Frames::TransmitRequest::SetTransmitOptions(const std::vector<TransmitOptions>& options)
{
    uint8_t byte = std::accumulate(options.begin(), options.end(), 0);
    SetDataByte(TRANSMIT_OPTIONS_OFFSET, byte);
}

std::vector<uint8_t>
BeeCoLL::Frames::TransmitRequest::GetPayload()
{
    std::vector<uint8_t> payload = GetData();
    // TODO: Check this number
    payload.erase(payload.begin(), payload.begin() + 11);
    return payload;
}

void
BeeCoLL::Frames::TransmitRequest::SetPayload(const std::vector<uint8_t>& payload)
{
    InsertDataAT(13, payload);
}
