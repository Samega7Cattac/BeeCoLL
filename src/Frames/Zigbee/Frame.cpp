#include "Frame.hh"

// STD headers
#include <cstring>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <memory>

using namespace BeeCoLL::Zigbee;



Frame::Frame(const std::vector<uint8_t>& frame) : BaseFrame(frame)
{
}


Frame::Frame(uint8_t frame_type) : BaseFrame(8)
{
    // Frame control init
    SetDataByte(0, 0);
    SetDataByte(1, 0);

    // Destination address init
    SetDataByte(2, 0);
    SetDataByte(3, 0);

    // Source address init
    SetDataByte(4, 0);
    SetDataByte(5, 0);
}

Frame::Frame(const Frame& other_frame) : 
    BeeCoLL::BaseFrame(other_frame)
{
}


Frame::~Frame()
{

}

void
Frame::SetDestinationAddress(AddressType destination_address)
{
    SetDataByte(DESTINATION_ADDRESS_FIELD_OFFSET,
                static_cast<uint8_t>(destination_address));
    SetDataByte(DESTINATION_ADDRESS_FIELD_OFFSET + 1,
                static_cast<uint8_t>(destination_address>>8));

}

void
Frame::SetSourceAddress(AddressType source_address)
{
    SetDataByte(SOURCE_ADDRESS_FIELD_OFFSET,
                static_cast<uint8_t>(source_address));
    SetDataByte(SOURCE_ADDRESS_FIELD_OFFSET + 1,
                static_cast<uint8_t>(source_address>>8));

}

AddressType 
Frame::GetSourceAddress()
{
    
    uint16_t value = GetDataByte(SOURCE_ADDRESS_FIELD_OFFSET + 1);
    value |= GetDataByte(SOURCE_ADDRESS_FIELD_OFFSET) << 8;

    return value;
}


void
Frame::SetDestinationIEEEAddress(IEEEAddressType destination_ieee_address)
{
    FrameControl* frame_control = GetFrameControlPtr();

    if (frame_control->destination_ieee_address == true)
    {
        for (size_t byte_index_offset = 0; byte_index_offset < sizeof(destination_ieee_address); byte_index_offset++)
        {
            SetDataByte(IEEE_ADDRESS_FIELDS_OFFSET + byte_index_offset, 
                        static_cast<uint8_t>(destination_ieee_address >> byte_index_offset*8));
        }
    }
    else
    {
        frame_control->destination_ieee_address = true;
        InsertData(IEEE_ADDRESS_FIELDS_OFFSET, 
                   std::vector<uint8_t>(
                        &destination_ieee_address,
                        &destination_ieee_address + sizeof(destination_ieee_address)
                   ));
    }
}

void
Frame::SetSourceIEEEAddress(IEEEAddressType source_ieee_address)
{
    FrameControl* frame_control = GetFrameControlPtr();

    unsigned int total_offset = IEEE_ADDRESS_FIELDS_OFFSET + frame_control->destination_ieee_address*8;

    if (frame_control->source_ieee_address == true)
    {
        //TODO mudar para uma função do BaseFrame
        for (size_t byte_index_offset = 0; byte_index_offset < sizeof(source_ieee_address); byte_index_offset++)
        {
            SetDataByte(total_offset + byte_index_offset, 
                        static_cast<uint8_t>(source_ieee_address >> byte_index_offset*8));
        }
    }
    else
    {
        frame_control->source_ieee_address = true;
        InsertData(total_offset, 
                   std::vector<uint8_t>(
                        &source_ieee_address,
                        &source_ieee_address + sizeof(source_ieee_address)
                   ));
    }
}

IEEEAddressType
Frame::GetSourceIEEEAddress()
{
    const FrameControl* frame_control = GetFrameControlPtr();

    IEEEAddressType address = 0;

    if (frame_control->destination_ieee_address == true)
    {
        for (size_t byte_index_offset = 0; byte_index_offset < sizeof(IEEE_ADDRESS_FIELDS_OFFSET); byte_index_offset++)
        {
            uint8_t data_byte = GetDataByte(IEEE_ADDRESS_FIELDS_OFFSET + byte_index_offset);
            address |= data_byte << byte_index_offset*sizeof(uint8_t);
        }
    }

    return address;
}


uint8_t
Frame::GetFrameType()
{
    return GetFrameControlPtr()->frame_type;
    
}

uint8_t
Frame::GetFrameHeaderOffset() const
{
    const FrameControl* frame_control = GetFrameControlPtr();
    uint8_t offset = 
        sizeof(FrameControl) + 2*sizeof(AddressType) +
        sizeof(IEEEAddressType)*(frame_control->destination_ieee_address + 
        frame_control->source_ieee_address);
    
    return offset;
}   



FrameControl*
Frame::GetFrameControlPtr()
{
    return reinterpret_cast<FrameControl*>(
                GetDataBytePtr(FrameOffsets::FRAME_CONTROL_OFFSET));
}

const FrameControl*
Frame::GetFrameControlPtr() const
{
    return reinterpret_cast<const FrameControl*>(
                GetDataBytePtr(FrameOffsets::FRAME_CONTROL_OFFSET));
}
