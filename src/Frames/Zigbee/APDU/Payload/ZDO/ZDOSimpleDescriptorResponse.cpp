#include "ZDOSimpleDescriptorResponse.hh"

using namespace BeeCoLL::Zigbee;

ZDOSimpleDescriptorResponse::ZDOSimpleDescriptorResponse(DataFrame& data_frame) : ZDOPayload(data_frame) 
{
    
}


uint8_t 
ZDOSimpleDescriptorResponse::GetEndpoint()
{
    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->endpoint;
}

uint16_t 
ZDOSimpleDescriptorResponse::GetProfileID()
{
    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->profile_id;
}

uint16_t 
ZDOSimpleDescriptorResponse::GetDeviceID()
{
    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->device_id;
}

uint8_t 
ZDOSimpleDescriptorResponse::GetInputClusterCount()
{
    uint8_t input_cluster_offset = m_data_frame.GetPayloadOffset() + sizeof(ZDOSimpleDescriptorStaticFields);

    return GetData().at(input_cluster_offset);
}

uint16_t 
ZDOSimpleDescriptorResponse::GetInputCluster(uint8_t input_cluster_index)
{
    uint8_t input_cluster_id_offset = 
        m_data_frame.GetPayloadOffset() +
        sizeof(ZDOSimpleDescriptorStaticFields) +
        input_cluster_index*sizeof(uint16_t);

    uint8_t cluster_id_1 = GetData().at(input_cluster_id_offset);
    uint8_t cluster_id_2 = GetData().at(input_cluster_id_offset + 1);

    uint16_t cluster_id = 
        static_cast<uint16_t>(cluster_id_1) + 
        static_cast<uint16_t>(cluster_id_2<<sizeof(uint8_t)); 

    return cluster_id;
}

uint8_t 
ZDOSimpleDescriptorResponse::GetOutputClusterCount()
{
    uint8_t output_cluster_offset = 
        m_data_frame.GetPayloadOffset() + 
        sizeof(ZDOSimpleDescriptorStaticFields) + 
        GetInputClusterCount();

    return GetData().at(output_cluster_offset);
}

uint16_t 
ZDOSimpleDescriptorResponse::GetOutputCluster(uint8_t output_cluster_index)
{
    uint8_t output_cluster_id_offset = 
        m_data_frame.GetPayloadOffset() + 
        sizeof(ZDOSimpleDescriptorStaticFields) + 
        GetInputClusterCount() +
        output_cluster_index*sizeof(uint16_t);

    uint8_t cluster_id_1 = GetData().at(output_cluster_id_offset);
    uint8_t cluster_id_2 = GetData().at(output_cluster_id_offset + 1);

    uint16_t cluster_id = 
        static_cast<uint16_t>(cluster_id_1) + 
        static_cast<uint16_t>(cluster_id_2<<sizeof(uint8_t)); 

    return cluster_id;
}


ZDOSimpleDescriptorStaticFields* 
ZDOSimpleDescriptorResponse::GetZDOSimpleDescriptorStaticFieldsPtr()
{
    uint8_t discovery_offset = GetZDOSimpleDescriptorOffset(); 

    return reinterpret_cast<ZDOSimpleDescriptorStaticFields*>(GetData().at(discovery_offset));
}

uint8_t
ZDOSimpleDescriptorResponse::GetZDOSimpleDescriptorOffset()
{
    return m_data_frame.GetPayloadOffset() /*+ sizeof(ZCLPayloadControl)*/;
}

