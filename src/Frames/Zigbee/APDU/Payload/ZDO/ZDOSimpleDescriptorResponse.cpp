#include "beecoll/Frames/Zigbee/APDU/Payload/ZDO/ZDOSimpleDescriptorResponse.hh"

using namespace BeeCoLL::Zigbee;

ZDOSimpleDescriptorResponse::ZDOSimpleDescriptorResponse(DataFrame& data_frame) : ZDOPayload(data_frame) 
{
    
}



enum ZDOSimpleDescriptorStatus 
ZDOSimpleDescriptorResponse::GetSimpleDescriptorStatus() const
{
    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->status;
}

uint16_t 
ZDOSimpleDescriptorResponse::GetTargetNetworkAddress() const
{

    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->target_network_address;
}

uint8_t 
ZDOSimpleDescriptorResponse::GetSimpleDescriptorLength() const
{
    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->simple_descriptor_length;
}


uint8_t 
ZDOSimpleDescriptorResponse::GetEndpoint() const
{
    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->endpoint;
}

uint16_t 
ZDOSimpleDescriptorResponse::GetProfileID() const
{
    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->profile_id;
}

uint16_t 
ZDOSimpleDescriptorResponse::GetDeviceID() const
{
    const ZDOSimpleDescriptorStaticFields* static_fields = GetZDOSimpleDescriptorStaticFieldsPtr();

    return static_fields->device_id;
}

uint8_t 
ZDOSimpleDescriptorResponse::GetInputClusterCount() const
{
    uint8_t input_cluster_offset = m_data_frame.GetPayloadOffset() + sizeof(ZDOSimpleDescriptorStaticFields);

    return GetDataByte(input_cluster_offset);
}

uint16_t 
ZDOSimpleDescriptorResponse::GetInputCluster(uint8_t input_cluster_index) const
{
    uint8_t input_cluster_id_offset = 
        m_data_frame.GetPayloadOffset() +
        sizeof(ZDOSimpleDescriptorStaticFields) +
        input_cluster_index*sizeof(uint16_t);

    uint8_t cluster_id_1 = GetDataByte(input_cluster_id_offset);
    uint8_t cluster_id_2 = GetDataByte(input_cluster_id_offset + 1);

    uint16_t cluster_id = 
        static_cast<uint16_t>(cluster_id_1) + 
        static_cast<uint16_t>(cluster_id_2<<8); 

    return cluster_id;
}

uint8_t 
ZDOSimpleDescriptorResponse::GetOutputClusterCount() const
{
    uint8_t output_cluster_offset = 
        m_data_frame.GetPayloadOffset() + 
        sizeof(ZDOSimpleDescriptorStaticFields) + 
        GetInputClusterCount();

    return GetDataByte(output_cluster_offset);
}

uint16_t 
ZDOSimpleDescriptorResponse::GetOutputCluster(uint8_t output_cluster_index) const 
{
    uint8_t output_cluster_id_offset = 
        m_data_frame.GetPayloadOffset() + 
        sizeof(ZDOSimpleDescriptorStaticFields) + 
        GetInputClusterCount() +
        output_cluster_index*sizeof(uint16_t);

    uint8_t cluster_id_1 = GetDataByte(output_cluster_id_offset);
    uint8_t cluster_id_2 = GetDataByte(output_cluster_id_offset + 1);

    uint16_t cluster_id = 
        static_cast<uint16_t>(cluster_id_1) + 
        static_cast<uint16_t>(cluster_id_2<<8); 

    return cluster_id;
}


ZDOSimpleDescriptorStaticFields* 
ZDOSimpleDescriptorResponse::GetZDOSimpleDescriptorStaticFieldsPtr()
{
    uint8_t discovery_offset = GetZDOSimpleDescriptorOffset(); 

    return reinterpret_cast<ZDOSimpleDescriptorStaticFields*>(GetData().data() + discovery_offset);
}

const ZDOSimpleDescriptorStaticFields* 
ZDOSimpleDescriptorResponse::GetZDOSimpleDescriptorStaticFieldsPtr() const
{
    uint8_t discovery_offset = GetZDOSimpleDescriptorOffset(); 

    return reinterpret_cast<const ZDOSimpleDescriptorStaticFields*>(GetData().data() + discovery_offset);
}

uint8_t
ZDOSimpleDescriptorResponse::GetZDOSimpleDescriptorOffset() const
{
    return m_data_frame.GetPayloadOffset() /*+ sizeof(ZCLPayloadControl)*/;
}

