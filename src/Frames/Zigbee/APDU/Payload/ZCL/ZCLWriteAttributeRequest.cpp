#include "ZCLWriteAttributeRequest.hh"

using namespace BeeCoLL::Zigbee;

ZCLWriteAttributeRequest::ZCLWriteAttributeRequest(DataFrame& data_frame) : 
     ZCLPayload(data_frame, ZCL_COMMAND_WRITE_ATTRIBUTE_REQUEST) 
{
}


void
ZCLWriteAttributeRequest::AddAttributeToRequest(uint16_t attribute_identifier,
                                                uint8_t attribute_data_type,
                                                const std::vector<uint8_t>& attribute_value)
{
    std::vector<uint8_t> attribute_data;
    attribute_data.reserve(3);
    attribute_data.push_back(static_cast<uint8_t>(attribute_identifier>>8));
    attribute_data.push_back(static_cast<uint8_t>(attribute_identifier));
    attribute_data.push_back(attribute_data_type);


    InsertData(GetPayloadOffset() + 
                    GetPayloadSize(),
               attribute_data);
    InsertData(GetPayloadOffset() + 
                    GetPayloadSize() + attribute_data.size(),
               attribute_value);
               //TODO FIx not changing payload size
}