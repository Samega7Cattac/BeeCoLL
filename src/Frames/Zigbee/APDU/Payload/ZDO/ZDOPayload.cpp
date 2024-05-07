#include "beecoll/Frames/Zigbee/APDU/Payload/ZDO/ZDOPayload.hh"

using namespace BeeCoLL::Zigbee;

ZDOPayload::ZDOPayload(DataFrame& data_frame) :
    m_data_frame(data_frame)
{
    
}

uint8_t 
ZDOPayload::GetPayloadOffset()
{
    return m_data_frame.GetPayloadOffset();
}

uint8_t 
ZDOPayload::GetPayloadSize()
{
    return m_data_frame.GetPayloadSize();
}

void 
ZDOPayload::InsertData(unsigned int byte_index, const std::vector<uint8_t>& data)
{
    m_data_frame.InsertData(byte_index, data);
}

void 
ZDOPayload::SetDataByte(unsigned int byte_index, uint8_t byte)
{
    m_data_frame.SetDataByte(byte_index, byte);
}

uint8_t 
ZDOPayload::GetDataByte(unsigned int byte_offset) const
{
    return m_data_frame.GetDataByte(byte_offset);
}


std::vector<uint8_t>& 
ZDOPayload::GetData()
{
    return m_data_frame.GetData();
}


std::vector<uint8_t>& 
ZDOPayload::GetData() const
{
    return m_data_frame.GetData();
}