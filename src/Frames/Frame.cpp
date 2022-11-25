#include "Frame.hh"

// STD headers
#include <cstring>
#include <algorithm>
#include <numeric>

using namespace BeeCoLL;

Frame::Frame(FrameType type, const std::vector<uint8_t>& data) :
    m_id(0),
    m_type(type),
    m_data(data)
{
    RecalculateDataSize();
    RecalculateChecksum();
}

#include <iostream>

Frame::Frame(const std::vector<uint8_t>& frame)
{
    if (frame[0] != START_DELIMITER)
    {
        std::cout << "NOT COOL" << std::endl;
        // TODO: throw something
    }
    m_length_msb = frame[1];
    m_length_lsb = frame[2];

    unsigned int data_size = m_length_lsb;
    data_size |= m_length_msb << 8;

    m_type = static_cast<FrameType>(frame[3]);

    for (unsigned int byte = 4; byte < 3 + data_size; ++byte)
    {
        m_data.push_back(frame[byte]);
    }

    RecalculateChecksum();
    if (CompareChecksum(frame[3 + data_size]) == false)
    {
        std::cout << "check frame failed" << std::endl;
    }
}

Frame::Frame(const Frame& other_frame) :
    m_response_types(other_frame.m_response_types),
    m_id(other_frame.m_id),
    m_length_msb(other_frame.m_length_msb),
    m_length_lsb(other_frame.m_length_lsb),
    m_type(other_frame.m_type),
    m_data(other_frame.m_data),
    m_checksum(other_frame.m_checksum)
{

}

Frame::~Frame()
{

}

std::vector<uint8_t>
Frame::GetData()
{
    return m_data;
}

void
Frame::SetData(const std::vector<uint8_t>& data)
{
    m_data = data;
    RecalculateDataSize();
    RecalculateChecksum();
}

unsigned char
Frame::GetDataByte(unsigned int byte_index)
{
    if (byte_index >= m_data.size())
    {
        // TODO: throw something
        std::cout << "byte out of scope of data" << std::endl;
        return 0;
    }
    return m_data[byte_index];
}

void
Frame::SetDataByte(unsigned int byte_index, unsigned char byte)
{
    if (byte_index >= m_data.size())
    {
        m_data.resize(byte_index + 1);
        RecalculateDataSize();
    }
    m_data[byte_index] = byte;
    RecalculateChecksum();
}

bool
Frame::GetDataBit(unsigned int byte_index, unsigned char bit_offset)
{
    if (byte_index > m_data.size())
    {
        // TODO: throw something
        std::cout << "get bit out of scope" << std::endl;
    }
    return GetDataByte(byte_index) << (7 - bit_offset);
}

bool
Frame::GetDataBit(unsigned int bit_index)
{
    return GetDataBit(bit_index / 8, bit_index % 8);
}

void
Frame::SetDataBit(unsigned int byte_index, unsigned char bit_offset, bool bit)
{
    if (byte_index > m_data.size())
    {
        m_data.resize(byte_index);
        RecalculateDataSize();
    }
    m_data[byte_index] |= (bit << (7 - bit_offset));
    RecalculateChecksum();
}

void
Frame::SetDataBit(unsigned int bit_index, bool bit)
{
    SetDataBit(bit_index / 8, bit_index % 8, bit);
}

bool
Frame::GetDataBitMask(unsigned int byte_index, unsigned char mask)
{
    if (byte_index > m_data.size())
    {
        // TODO: throw something
        std::cout << "get bit out of scope" << std::endl;
    }
    return GetDataByte(byte_index) & mask;
}

void
Frame::InsertDataAT(unsigned int byte_index, const std::vector<uint8_t>& data)
{
    if (byte_index + data.size() > m_data.size())
    {
        // TODO: throw something
        std::cout << "get bit out of scope" << std::endl;
        m_data.resize(byte_index + data.size());
    }
    for (unsigned int byte = 0; byte < data.size(); ++byte)
    {
        m_data[byte_index + byte] = data[byte];
    }
    RecalculateDataSize();
    RecalculateChecksum();
}

FrameType
Frame::GetType() const
{
    return m_type;
}

void
Frame::SetType(FrameType type)
{
    if (type > INPUT_FRAME_DELIMITER)
    {
        // TODO: throw something
    }
    m_type = type;
    RecalculateChecksum();
}

bool
Frame::CompareChecksum(unsigned char other_checksum)
{
    if (m_checksum == other_checksum)
    {
        return true;
    }
    return false;
}

std::vector<uint8_t>
Frame::GetFrame() const
{
    std::vector<uint8_t> frame;
    frame.push_back(START_DELIMITER);
    frame.push_back(m_length_msb);
    frame.push_back(m_length_lsb);
    frame.push_back(m_type);
    std::copy(m_data.begin(), m_data.end(), std::back_inserter(frame));
    frame.push_back(m_checksum);
    return frame;
}

uint8_t
Frame::GetID() const
{
    return m_id;
}

std::vector<uint8_t>
Frame::GetResponseTypes() const
{
    return m_response_types;
}

void
Frame::SetID(uint8_t id)
{
    m_id = id;
}

void
Frame::SetResponseTypes(const std::vector<uint8_t>& response_types)
{
    m_response_types = response_types;
}

void
Frame::RecalculateChecksum()
{
    unsigned char sum = m_type;
    sum += std::accumulate(m_data.begin(), m_data.end(), 0);
    m_checksum = 0xFF - sum;
}

void
Frame::RecalculateDataSize()
{
    uint16_t frame_data_length = 1 + m_data.size();

    m_length_msb = frame_data_length >> 8;
    m_length_lsb = frame_data_length;
}
