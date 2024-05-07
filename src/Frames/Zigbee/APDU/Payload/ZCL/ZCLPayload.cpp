#include "beecoll/Frames/Zigbee/APDU/Payload/ZCL/ZCLPayload.hh"

using namespace BeeCoLL::Zigbee;

constexpr unsigned int ZCL_PAYLOAD_HEADER_INITIAL_SIZE = 3;
constexpr unsigned int ZCL_PAYLOAD_MANUFACTURER_SPECIFIC_CODE_OFFSET = 1;


enum ZCLCommandID
ZCLPayload::GetZCLPayloadCommandIdentifier(DataFrame& data_frame)
{
    uint8_t payload_offset = data_frame.GetPayloadOffset();

    ZCLPayloadControl payload_control = static_cast<ZCLPayloadControl>(data_frame.GetDataByte(payload_offset)); 

    return static_cast<enum ZCLCommandID>(data_frame.GetDataByte(
        data_frame.GetPayloadOffset() + 
        sizeof(ZCLPayloadControl) +
        payload_control.manufacturer_specific*sizeof(uint16_t) + 
        sizeof(uint8_t)));
}

ZCLPayload::ZCLPayload(DataFrame& data_frame, uint8_t command_identifier) :
    m_data_frame(data_frame)
{
    m_data_frame.SetDataByte(m_data_frame.GetPayloadOffset(), 0);

    uint8_t transaction_sequence_offset = 
        GetPayloadOffset() +
        IsManufacturerSpecific()*sizeof(uint16_t);

    InsertData(transaction_sequence_offset, {0, command_identifier});
    m_data_frame.SetPayloadSize(m_data_frame.GetPayloadSize() + 2);
}

ZCLPayload::ZCLPayload(DataFrame& data_frame) :
    m_data_frame(data_frame)
{
}

void
ZCLPayload::SetManufacturerCode(uint16_t manufacturer_code)
{
    ZCLPayloadControl* payload_control = GetPayloadControlPtr();

    if(payload_control->manufacturer_specific)
    {
        m_data_frame.SetDataByte(m_data_frame.GetPayloadOffset() + 
                                    ZCL_PAYLOAD_MANUFACTURER_SPECIFIC_CODE_OFFSET,
                                static_cast<uint8_t>(manufacturer_code >> 8));


        m_data_frame.SetDataByte(m_data_frame.GetPayloadOffset() + 
                                    ZCL_PAYLOAD_MANUFACTURER_SPECIFIC_CODE_OFFSET + 1,
                                static_cast<uint8_t>(manufacturer_code));
    }
    else
    {
        payload_control->manufacturer_specific = true;

        m_data_frame.InsertData(m_data_frame.GetPayloadOffset() + 
                                    ZCL_PAYLOAD_MANUFACTURER_SPECIFIC_CODE_OFFSET,
                                std::vector<uint8_t>(reinterpret_cast<uint8_t*>(&manufacturer_code),
                                                     reinterpret_cast<uint8_t*>(&manufacturer_code + 
                                                        sizeof(manufacturer_code))));
    }
}


uint8_t 
ZCLPayload::GetPayloadOffset()
{
    return m_data_frame.GetPayloadOffset();
}

uint8_t 
ZCLPayload::GetPayloadSize()
{
    return m_data_frame.GetPayloadSize();
}


bool 
ZCLPayload::IsManufacturerSpecific()
{
    return GetPayloadControlPtr()->manufacturer_specific;
}


ZCLPayloadControl*
ZCLPayload::GetPayloadControlPtr()
{
    uint8_t payload_offset = m_data_frame.GetPayloadOffset();

    uint8_t* payload = &m_data_frame.GetData().at(payload_offset);

    return reinterpret_cast<ZCLPayloadControl*>(payload);
}

void 
ZCLPayload::InsertData(unsigned int byte_index, const std::vector<uint8_t>& data)
{
    m_data_frame.InsertData(byte_index, data);
}


uint8_t 
ZCLPayload::GetDataByte(unsigned int byte_offset)
{
    return m_data_frame.GetDataByte(byte_offset);
}


std::vector<uint8_t>& 
ZCLPayload::GetData()
{
    return m_data_frame.GetData();
}




