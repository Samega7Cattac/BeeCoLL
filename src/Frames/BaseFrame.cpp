#include "BaseFrame.hh"

// STD headers
#include <cstring>
#include <algorithm>
#include <numeric>

#include <iostream>



BeeCoLL::BaseFrame::BaseFrame() :
    m_id(0)
{
}

BeeCoLL::BaseFrame::BaseFrame(unsigned int initial_frame_byte_size) :
    m_id(0)
{
    m_data.resize(initial_frame_byte_size);
}

BeeCoLL::BaseFrame::BaseFrame(const BeeCoLL::BaseFrame& other_frame) :
    m_id(other_frame.m_id),
    m_data(other_frame.m_data)
{
}

BeeCoLL::BaseFrame::BaseFrame(const std::vector<uint8_t>& frame) :
    m_data(frame)
{
}

BeeCoLL::BaseFrame::~BaseFrame()
{

}

std::vector<uint8_t>
BeeCoLL::BaseFrame::GetFrame() const
{
    return m_data;
}

std::vector<uint8_t>
BeeCoLL::BaseFrame::GetData() const
{
    return m_data;
}

std::vector<uint8_t>&
BeeCoLL::BaseFrame::GetData()
{
    return m_data;
}


std::size_t
BeeCoLL::BaseFrame::GetDataSize() const
{
    return m_data.size();
}

void
BeeCoLL::BaseFrame::SetData(const std::vector<uint8_t>& data)
{
    m_data = data;
}

void
BeeCoLL::BaseFrame::SetDataByte(unsigned int byte_index, uint8_t byte)
{
    if (byte_index >= m_data.size())
    {
        m_data.resize(byte_index + 1);
    }
    m_data[byte_index] = byte;
}

uint8_t
BeeCoLL::BaseFrame::GetDataByte(unsigned int byte_index) const
{
    if (byte_index >= m_data.size())
    {
        // TODO: throw something
        std::cout << "byte out of scope of data" << std::endl;
        return 0;
    }
    return m_data[byte_index];
}

uint8_t*
BeeCoLL::BaseFrame::GetDataBytePtr(unsigned int byte_index)
{
    if (byte_index >= m_data.size())
    {
        // TODO: throw something
        std::cout << "byte out of scope of data" << std::endl;
        return 0;
    }
    return &m_data[byte_index];
}

bool
BeeCoLL::BaseFrame::GetDataBit(unsigned int byte_index, uint8_t bit_offset) const
{
    if (byte_index > m_data.size())
    {
        // TODO: throw something
        std::cout << "get bit out of scope" << std::endl;
    }
    return GetDataByte(byte_index) << (7 - bit_offset);
}

bool
BeeCoLL::BaseFrame::GetDataBit(unsigned int bit_index) const
{
    return GetDataBit(bit_index / 8, bit_index % 8);
}


void
BeeCoLL::BaseFrame::SetDataBit(unsigned int byte_index, uint8_t bit_offset, bool bit)
{
    if (byte_index > m_data.size())
    {
        m_data.resize(byte_index);
    }
    m_data[byte_index] |= (bit << (7 - bit_offset));
}

void
BeeCoLL::BaseFrame::SetDataBit(unsigned int bit_index, bool bit)
{
    SetDataBit(bit_index / 8, bit_index % 8, bit);
}

bool
BeeCoLL::BaseFrame::GetDataBitMask(unsigned int byte_index, uint8_t mask) const
{
    if (byte_index > m_data.size())
    {
        // TODO: throw something
        std::cout << "get bit out of scope" << std::endl;
    }
    return GetDataByte(byte_index) & mask;
}

void
BeeCoLL::BaseFrame::InsertData(unsigned int byte_index, const std::vector<uint8_t>& data)
{
    /*if (byte_index + data.size() > m_data.size())
    {
        // TODO: throw something
        std::cout << "get bit out of scope" << std::endl;
        m_data.resize(byte_index + data.size());
    }*/
    m_data.insert(m_data.begin() + byte_index, data.begin(), data.end());
}

void 
BeeCoLL::BaseFrame::EraseData(unsigned int start_position, unsigned int end_position)
{
    if (end_position > m_data.size() || start_position >= end_position)
    {
        return;
    }
    m_data.erase(m_data.begin() + start_position, m_data.begin() + end_position + 1);
}


void 
BeeCoLL::BaseFrame::EraseData(unsigned int position)
{
    if (position > m_data.size())
    {
        return;
    }
    m_data.erase(m_data.begin() + position, m_data.begin() + position + 1);
}


uint8_t
BeeCoLL::BaseFrame::GetID() const
{
    return m_id;
}

void
BeeCoLL::BaseFrame::SetID(uint8_t id)
{
    m_id = id;
}

