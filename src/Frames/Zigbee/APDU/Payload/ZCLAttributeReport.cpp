#include "ZCLAttributeReport.hh"

using namespace BeeCoLL::Zigbee;

constexpr unsigned int ZCL_COMMAND_ATTRIBUTE_REPORT = 0x0a;

ZCLAttributeReport::ZCLAttributeReport(DataFrame& data_frame) : ZCLPayload(data_frame)
{
    UpdateAttributeListSize();
}


ZCLAttributeReport::Attribute
ZCLAttributeReport::GetAttribute(uint8_t attribute_index)
{
    if (attribute_index > m_attribute_list_size)
    {
        //TODO throw error
    }

    Attribute attribute;


    uint8_t attribute_size = 0;
    uint8_t payload_offset = GetPayloadOffset();

    for(uint8_t attribute_i = 0; attribute_i <= attribute_index; attribute_i++)
    {
        uint8_t attribute_identifier_offset = payload_offset;
        uint8_t attribute_datatype_offset = payload_offset + 2;
        uint8_t attribute_data_offset = payload_offset + 3;

        enum ZCLAttributeDataType attribute_datatype = static_cast<ZCLAttributeDataType>(GetDataByte(attribute_datatype_offset));
    

        uint8_t attribute_id_0 = GetDataByte(attribute_identifier_offset);
        uint8_t attribute_id_1 = GetDataByte(attribute_identifier_offset + 1);

        

        switch (attribute_datatype)
        {

        case ZCL_DATATYPE_FLOAT:
            if (attribute_i == attribute_index)
            {
                for (uint8_t size = 0; size < sizeof(float); size++)
                {
                    attribute.attribute_value.push_back(
                        GetDataByte(attribute_data_offset + size));
                }
            }
            payload_offset = attribute_data_offset + 4;
            attribute_size++;
            break;

        case ZCL_DATATYPE_INT32:
            if (attribute_i == attribute_index)
            {
                for (uint8_t size = 0; size < sizeof(int32_t); size++)
                {
                    attribute.attribute_value.push_back(
                        GetDataByte(attribute_data_offset + size));
                }
            }
            payload_offset = attribute_data_offset + 4;
            attribute_size++;
            break;

        case ZCL_DATATYPE_UINT16:
            if (attribute_i == attribute_index)
            {
                for (uint8_t size = 0; size < sizeof(uint16_t); size++)
                {
                    attribute.attribute_value.push_back(
                        GetDataByte(attribute_data_offset + size));
                }
            }
            payload_offset = attribute_data_offset + 2;
            attribute_size++;
            break;
        
        default:
            break;
        }

        if (attribute_i == attribute_index)
        {
            attribute.attribute_id = (attribute_id_1<<8) | attribute_id_0; 
            attribute.data_type = attribute_datatype;
            return attribute;
        }
    
    }

    // TODO  THROW ERROR
    return Attribute();
}

uint8_t
ZCLAttributeReport::GetAttributeListSize() const
{
    return m_attribute_list_size;
}


void
ZCLAttributeReport::UpdateAttributeListSize()
{

    bool has_next_attribute = true;
    uint8_t payload_offset = GetPayloadOffset();
    uint8_t attribute_size = 0;

    while(has_next_attribute == true)
    {
        if (payload_offset > GetPayloadSize())
        {
            return;
        }
        //uint8_t attribute_identifier_offset = payload_offset;
        uint8_t attribute_datatype_offset = payload_offset + 2;
        //uint8_t attribute_data_offset = payload_offset + 3;

        enum ZCLAttributeDataType attribute_datatype = static_cast<ZCLAttributeDataType>(GetDataByte(attribute_datatype_offset));
    
        switch (attribute_datatype)
        {

        case ZCL_DATATYPE_FLOAT:
            payload_offset += 2 + 1 + 4;
            attribute_size++;
            break;

        case ZCL_DATATYPE_INT32:
            payload_offset += 2 + 1 + 4;
            attribute_size++;
            break;

        case ZCL_DATATYPE_UINT16:
            payload_offset += 2 + 1 + 2;
            attribute_size++;
            break;
        
        default:
            has_next_attribute = false;
            break;
        }
    
    }

    m_attribute_list_size = attribute_size;
}