#include "ZDODeviceAnnounce.hh"
 
using namespace BeeCoLL::Zigbee;

ZDODeviceAnnounce::ZDODeviceAnnounce(DataFrame& data_frame) : ZDOPayload(data_frame)
{

}

ZDODeviceAnnounce::~ZDODeviceAnnounce()
{

}


uint16_t 
ZDODeviceAnnounce::GetNetworkAddress()
{
    uint64_t network_address_m = GetZDODeviceAnnouncePtr()->network_address;

    uint16_t network_address;
    uint8_t* network_address_l = reinterpret_cast<uint8_t*>(&network_address);
    
    *(network_address_l + 0) = static_cast<uint8_t>(network_address_m >> 8*1);
    *(network_address_l + 1) = static_cast<uint8_t>(network_address_m >> 8*0);

    return network_address;
}

uint64_t 
ZDODeviceAnnounce::GetIEEEAddress()
{
    uint64_t ieee_address_m = GetZDODeviceAnnouncePtr()->ieee_address;

    uint64_t ieee_address;
    uint8_t* ieee_address_l = reinterpret_cast<uint8_t*>(&ieee_address);
    
    *(ieee_address_l + 0) = static_cast<uint8_t>(ieee_address_m >> 8*7);
    *(ieee_address_l + 1) = static_cast<uint8_t>(ieee_address_m >> 8*6);
    *(ieee_address_l + 2) = static_cast<uint8_t>(ieee_address_m >> 8*5);
    *(ieee_address_l + 3) = static_cast<uint8_t>(ieee_address_m >> 8*4);
    *(ieee_address_l + 4) = static_cast<uint8_t>(ieee_address_m >> 8*3);
    *(ieee_address_l + 5) = static_cast<uint8_t>(ieee_address_m >> 8*2);
    *(ieee_address_l + 6) = static_cast<uint8_t>(ieee_address_m >> 8*1);
    *(ieee_address_l + 7) = static_cast<uint8_t>(ieee_address_m >> 8*0);

    return ieee_address;
}

const ZDODeviceAnnounceFields* 
ZDODeviceAnnounce::GetZDODeviceAnnouncePtr() const
{
    uint8_t offset = GetZDODeviceAnnounceOffset();

    return reinterpret_cast<const ZDODeviceAnnounceFields*>(GetData().data() + offset);
}


uint8_t 
ZDODeviceAnnounce::GetZDODeviceAnnounceOffset() const
{
    return m_data_frame.GetPayloadOffset();
}