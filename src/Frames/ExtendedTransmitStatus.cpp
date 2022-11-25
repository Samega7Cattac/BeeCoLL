#include "ExtendedTransmitStatus.hh"

using namespace BeeCoLL;
using namespace BeeCoLL::Frames;

constexpr uint8_t FRAMEID_OFFSET = 0;
constexpr uint8_t DEST_ADDRESS_MSB_OFFSET = 1;
constexpr uint8_t DEST_ADDRESS_LSB_OFFSET = 2;
constexpr uint8_t RETRY_COUNT_OFFSET = 3;
constexpr uint8_t DELIVERY_STATUS_OFFSET = 4;
constexpr uint8_t DISCOVERY_STATUS_OFFSET = 5;

static uint8_t frame_id = 1;

ExtendedTransmitStatus::ExtendedTransmitStatus(const std::vector<uint8_t>& frame_data) : 
    Frame(FrameType::TRANSMIT_STATUS, frame_data)
{
    SetFrameID(frame_id++);
}

ExtendedTransmitStatus::ExtendedTransmitStatus(const Frame& other) : 
    Frame(other)
{

}

ExtendedTransmitStatus::~ExtendedTransmitStatus()
{

}

uint8_t
ExtendedTransmitStatus::GetFrameID()
{
    return GetDataByte(FRAMEID_OFFSET);
}

void
ExtendedTransmitStatus::SetFrameID(uint8_t frame_id)
{
    SetID(frame_id);
    SetDataByte(FRAMEID_OFFSET, frame_id);
}

uint16_t
ExtendedTransmitStatus::GetDestNetworkAddr()
{
    uint16_t address = GetDataByte(DEST_ADDRESS_LSB_OFFSET);
    address |= GetDataByte(DEST_ADDRESS_MSB_OFFSET) << sizeof(uint8_t);
    return address;
}

uint8_t
ExtendedTransmitStatus::GetRetryCount()
{
    return GetDataByte(RETRY_COUNT_OFFSET);
}

DeliveryStatus
ExtendedTransmitStatus::GetDeliveryStatus()
{
    return static_cast<DeliveryStatus>(GetDataByte(DELIVERY_STATUS_OFFSET));
}

DiscoveryStatus
ExtendedTransmitStatus::GetDiscoveryStatus()
{
    return static_cast<DiscoveryStatus>(GetDataByte(DISCOVERY_STATUS_OFFSET));
}
