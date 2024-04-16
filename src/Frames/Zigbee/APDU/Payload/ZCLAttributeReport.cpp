#include "ZCLAttributeReport.hh"

using namespace BeeCoLL::Zigbee;

constexpr unsigned int ZCL_COMMAND_ATTRIBUTE_REPORT = 0x0a;

ZCLAttributeReport::ZCLAttributeReport(DataFrame& data_frame) : ZCLPayload(data_frame)
{
    UpdateAttributeListSize();
}


ZCLAttribute
ZCLAttributeReport::GetAttribute(uint8_t attribute_index)
{
    if (attribute_index > m_attribute_list_size)
    {
        //TODO throw error
    }

    


    uint8_t attribute_size = 0;
    uint8_t payload_offset = GetPayloadOffset();

    ZCLAttribute attribute;

    for(uint8_t attribute_i = 0; attribute_i <= attribute_index; attribute_i++)
    {
        uint8_t attribute_identifier_offset = payload_offset;
        uint8_t attribute_datatype_offset = payload_offset + 2;
        uint8_t attribute_data_offset = payload_offset + 3;


        enum ZCLAttributeDataType attribute_datatype = static_cast<ZCLAttributeDataType>(GetDataByte(attribute_datatype_offset));

        uint8_t attribute_data_length;

        switch (attribute_datatype)
        {
        case ZCLAttributeDataType::ZCL_DATATYPE_INT32 :
        case ZCLAttributeDataType::ZCL_DATATYPE_UINT32 :
        case ZCLAttributeDataType::ZCL_DATATYPE_FLOAT :
            attribute_data_length = 4;
            break;
        
        default:
            attribute_data_length = 2;
            break;
        }

        uint8_t attribute_id_0 = GetDataByte(attribute_identifier_offset);
        uint8_t attribute_id_1 = GetDataByte(attribute_identifier_offset + 1);

        attribute = ZCLAttribute((attribute_id_1<<8) | attribute_id_0, attribute_datatype);
        
        std::vector<uint8_t>& data = GetData();

        attribute.SetAttributeValueVector(std::vector<uint8_t>(data.data() + attribute_data_offset, data.data() + attribute_data_offset + attribute_data_length));
       
        payload_offset += 3 + attribute_data_length;
    }

    // TODO  THROW ERROR
    return attribute;
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
        case ZCL_DATATYPE_UINT32:
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