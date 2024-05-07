#include "beecoll/Frames/Zigbee/APDU/Payload/ZDO/ZDOSimpleDescriptorRequest.hh"

using namespace BeeCoLL::Zigbee;

ZDOSimpleDescriptorRequest::ZDOSimpleDescriptorRequest(DataFrame& data_frame) : ZDOPayload(data_frame) 
{
    data_frame.SetDestinationEndpoint(0);
    data_frame.SetClusterID(0x0004);
    data_frame.SetProfileID(0x0000);
}



void 
ZDOSimpleDescriptorRequest::SetTargetNetworkAddress(uint16_t network_address)
{
    SetDataByte(m_data_frame.GetPayloadOffset(), static_cast<uint8_t>(network_address));
    SetDataByte(m_data_frame.GetPayloadOffset() + 1, static_cast<uint8_t>(network_address>>8));
}

void 
ZDOSimpleDescriptorRequest::SetTargetEndpoint(uint8_t endpoint)
{
    SetDataByte(m_data_frame.GetPayloadOffset() + 2, endpoint);
}

