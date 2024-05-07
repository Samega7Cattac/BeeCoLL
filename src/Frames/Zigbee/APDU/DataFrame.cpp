#include "DataFrame.hh"

// STD headers
#include <cstring>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <memory>

using namespace BeeCoLL::Zigbee;

DataFrame::DataFrame() : 
    APDUFrame(APDUFrameType::DATA_APDUFRAME_TYPE),
    m_delivery_mode_address_length(0),
    m_payload_offset(GetFrameHeaderOffset() + 7),
    m_payload_size(0)
{
    SetDeliveryModeType(DeliveryType::NULL_DELIVERY_MODE);
}

DataFrame::DataFrame(const DataFrame& other_frame) : 
    APDUFrame(other_frame)
{
    SetPayloadOffset(other_frame.GetPayloadOffset());
    m_delivery_mode_address_length = other_frame.GetDeliveryModeAddressLength();

    SetPayloadSize(other_frame.GetPayloadSize());                                                                                                                                                                                                                                       
}

                    
DataFrame::DataFrame(const std::vector<uint8_t>& frame) : APDUFrame(frame)
{
    uint8_t delivery_type = GetAPDUFrameControlPtr()->delivery_type;

    switch (delivery_type)
    {
    case DeliveryType::UNICAST_DELIVERY_MODE :
        m_delivery_mode_address_length = 1;
        SetPayloadOffset(GetFrameHeaderOffset() + 8);
        break;
    
    case DeliveryType::GROUP_DELIVERY_MODE :
        m_delivery_mode_address_length = 2;
        SetPayloadOffset(GetFrameHeaderOffset() + 9);
        break;
    
    default:
        m_delivery_mode_address_length = 0;
        SetPayloadOffset(GetFrameHeaderOffset() + 7);
        break;
    }

    SetPayloadSize(frame.size() - GetPayloadOffset());
}


DataFrame::~DataFrame()
{

}


void
DataFrame::SetProfileID(uint16_t profile_id)
{

    SetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 2,
                static_cast<uint8_t>(profile_id));


    SetDataByte(GetFrameHeaderOffset() +
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 3,
                static_cast<uint8_t>(profile_id>>8));
}

void
DataFrame::SetClusterID(uint16_t cluster_id)
{

    SetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length,
                static_cast<uint8_t>(cluster_id));


    SetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 1,
                static_cast<uint8_t>(cluster_id>>8));
}


void
DataFrame::SetSourceEndpoint(uint8_t source_endpoint)
{
    SetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 4,
                source_endpoint);
}

uint8_t
DataFrame::GetSourceEndpoint() const
{
    return GetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 4);
}

void
DataFrame::SetDestinationEndpoint(uint8_t destination_endpoint)
{
    SetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET,
                destination_endpoint);
}

uint8_t
DataFrame::GetDestinationEndpoint() const
{
    return GetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET);
}

void
DataFrame::SetAPSCounter(uint8_t aps_counter)
{
    SetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 5,
                aps_counter);
}


uint16_t 
DataFrame::GetProfileID() const
{

    uint8_t profileid_1 = GetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 2);


    uint8_t profileid_2 = GetDataByte(GetFrameHeaderOffset() +
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 3);

    uint16_t profile_id = static_cast<uint16_t>(profileid_2)<<8 | static_cast<uint16_t>(profileid_1);

    return profile_id;
}

uint16_t 
DataFrame::GetClusterID() const
{

    uint8_t clusterid_1 = GetDataByte(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length);


    uint8_t clusterid_2 = GetDataByte(GetFrameHeaderOffset() +
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 
                    m_delivery_mode_address_length + 1);

    uint16_t cluster_id = static_cast<uint16_t>(clusterid_2<<8) | static_cast<uint16_t>(clusterid_1);

    return cluster_id;
}

void
DataFrame::SetDeliveryModeType(DeliveryType delivery_type)
{
    APDUFrameControl* frame_control = GetAPDUFrameControlPtr();
    frame_control->delivery_type = delivery_type;
}

void
DataFrame::SetUnicastDeliveryMode(uint8_t endpoint_address)
{
    UnsetDeliveryModeAdresses();
    SetDeliveryModeType(DeliveryType::UNICAST_DELIVERY_MODE);

    m_delivery_mode_address_length = 1;
    SetPayloadOffset(GetFrameHeaderOffset() + 8);
    

    InsertData(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET,
               std::vector<uint8_t>((uint8_t*)&endpoint_address,
                                    (uint8_t*)&endpoint_address + sizeof(endpoint_address)));
}

void
DataFrame::SetGroupDeliveryMode(uint16_t group_address)
{
    UnsetDeliveryModeAdresses();
    SetDeliveryModeType(DeliveryType::GROUP_DELIVERY_MODE);

    m_delivery_mode_address_length = 2;
    SetPayloadOffset(GetFrameHeaderOffset() + 9);

    InsertData(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET,
               std::vector<uint8_t>((uint8_t*)&group_address,
                                    (uint8_t*)&group_address + sizeof(group_address)));
}


void
DataFrame::SetBroadcastDeliveryMode()
{
    UnsetDeliveryModeAdresses();
    SetDeliveryModeType(DeliveryType::BROADCAST_DELIVERY_MODE);

    m_delivery_mode_address_length = 2;
    SetPayloadOffset(GetFrameHeaderOffset() + 9);
    
    uint16_t group_address = 0xffff;

    InsertData(GetFrameHeaderOffset() + 
                    APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET,
               std::vector<uint8_t>((uint8_t*)&group_address,
                                    ((uint8_t*)&group_address) + sizeof(group_address)));
}

unsigned int
DataFrame::GetDeliveryModeAddressLength() const
{
    return m_delivery_mode_address_length;
}

void 
DataFrame::UnsetDeliveryModeAdresses()
{
    APDUFrameControl* frame_control = GetAPDUFrameControlPtr();

    switch (frame_control->delivery_type)
    {
    case DeliveryType::UNICAST_DELIVERY_MODE :
        EraseData(GetFrameHeaderOffset() + APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET);
        break;
    
    case DeliveryType::BROADCAST_DELIVERY_MODE :
    case DeliveryType::GROUP_DELIVERY_MODE :
        EraseData(GetFrameHeaderOffset() + APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET);
        EraseData(GetFrameHeaderOffset() + APDUFrameOffsets::DELIVERY_ADDRESS_FIELD_OFFSET + 1);
        break;
    
    default:
        break;
    }

}

void
DataFrame::SetPayloadOffset(unsigned int payload_offset)
{
    m_payload_offset = payload_offset;
}

unsigned int
DataFrame::GetPayloadOffset() const
{
    return m_payload_offset;
}

void
DataFrame::SetPayloadSize(unsigned int payload_size)
{
    m_payload_size = payload_size;
}

unsigned int
DataFrame::GetPayloadSize() const
{
    return m_payload_size;
}
