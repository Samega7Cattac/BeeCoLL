#include "ZCLAttribute.hh"

using namespace BeeCoLL::Zigbee;

ZCLAttribute::ZCLAttribute() :
    m_attribute_id(0xFFFF),
    m_data_type(ZCLAttributeDataType::ZCL_DATATYPE_NULL)
{
}


ZCLAttribute::ZCLAttribute(uint16_t attribute_id,
                           enum ZCLAttributeDataType data_type) :
    m_data_type(data_type),
    m_attribute_id(attribute_id)
{
    
};

template<class T>
ZCLAttribute::ZCLAttribute(uint16_t attribute_id, 
                           enum ZCLAttributeDataType data_type, T value) :
    ZCLAttribute(data_type, attribute_id)
{
    m_attribute_value.reserve(sizeof(T));
    for (uint8_t size = 0; size < sizeof(T); size++)
    {
        m_attribute_value.push_back(
            static_cast<uint8_t>(value >> size*8));
    }
}

ZCLAttribute::~ZCLAttribute()
{

};


void 
ZCLAttribute::SetAttributeValueVector(const std::vector<uint8_t>& attribute_value)
{
    m_attribute_value = attribute_value;
}

std::vector<uint8_t> 
ZCLAttribute::GetAttributeValueVector() const
{
    return m_attribute_value;
}


// template<class T>
// void 
// ZCLAttribute::SetAttributeValueLSB(T attribute_value)
// {
//     m_attribute_value.clear();
//     m_attribute_value.reserve(sizeof(T));
//     for (uint8_t size = 0; size < sizeof(T); size++)
//     {
//         m_attribute_value.push_back(
//             static_cast<uint8_t>(attribute_value >> (sizeof(T) - size - 1)*8));
//     }
// }

// template<class T>
// T 
// ZCLAttribute::GetAttributeValue() const
// {
//     T value;
//     for (uint8_t size = 0; size <= sizeof(T); size++)
//     {
//         value |= m_attribute_value[sizeof(T) - 1 - size]<<size*8;
//     }

//     return value;
// }


uint16_t 
ZCLAttribute::GetAttributeID() const
{
    return m_attribute_id;
}

ZCLAttributeDataType
ZCLAttribute::GetDataType() const
{
    return m_data_type;
}