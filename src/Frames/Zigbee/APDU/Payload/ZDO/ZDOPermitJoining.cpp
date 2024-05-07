#include "beecoll/Frames/Zigbee/APDU/Payload/ZDO/ZDOPermitJoining.hh"

using namespace BeeCoLL::Zigbee;

ZDOPermitJoining::ZDOPermitJoining(DataFrame& data_frame) : ZDOPayload(data_frame) 
{
    data_frame.SetDestinationEndpoint(0);
    data_frame.SetClusterID(0x0036);
    data_frame.SetProfileID(0x0000);
}

void 
ZDOPermitJoining::SetPermitDuration(uint8_t duration)
{
    SetDataByte(m_data_frame.GetPayloadOffset(), duration);
}

