#include "ExtendedTransmitStatus.hh"

constexpr uint8_t FRAMEID_OFFSET = 0;
constexpr uint8_t DEST_ADDRESS_MSB_OFFSET = 1;
constexpr uint8_t DEST_ADDRESS_LSB_OFFSET = 2;
constexpr uint8_t RETRY_COUNT_OFFSET = 3;
constexpr uint8_t DELIVERY_STATUS_OFFSET = 4;
constexpr uint8_t DISCOVERY_STATUS_OFFSET = 5;

BeeCoLL::Frames::ExtendedTransmitStatus::ExtendedTransmitStatus(const std::vector<uint8_t>& frame_data) : 
    Frame(TRANSMIT_STATUS_FRAME_ID, frame_data)
{

}

BeeCoLL::Frames::ExtendedTransmitStatus::ExtendedTransmitStatus(const Frame& other) : 
    Frame(other)
{

}

BeeCoLL::Frames::ExtendedTransmitStatus::~ExtendedTransmitStatus()
{

}

uint8_t
BeeCoLL::Frames::ExtendedTransmitStatus::GetFrameID()
{
    return GetDataByte(FRAMEID_OFFSET);
}

uint16_t
BeeCoLL::Frames::ExtendedTransmitStatus::GetDestNetworkAddr()
{
    uint16_t address = GetDataByte(DEST_ADDRESS_LSB_OFFSET);
    address |= GetDataByte(DEST_ADDRESS_MSB_OFFSET) << sizeof(uint8_t);
    return address;
}

uint8_t
BeeCoLL::Frames::ExtendedTransmitStatus::GetRetryCount()
{
    return GetDataByte(RETRY_COUNT_OFFSET);
}

BeeCoLL::Frames::DeliveryStatus
BeeCoLL::Frames::ExtendedTransmitStatus::GetDeliveryStatus()
{
    return static_cast<DeliveryStatus>(GetDataByte(DELIVERY_STATUS_OFFSET));
}

BeeCoLL::Frames::DiscoveryStatus
BeeCoLL::Frames::ExtendedTransmitStatus::GetDiscoveryStatus()
{
    return static_cast<DiscoveryStatus>(GetDataByte(DISCOVERY_STATUS_OFFSET));
}
