#include "beecoll/Frames/Xbee/Frame.hh"

// STD headers
#include <cstring>
#include <algorithm>
#include <numeric>

using namespace BeeCoLL::Xbee;

Frame::Frame(uint8_t type, const std::vector<uint8_t>& data) //: BeeCoLL::BaseFrame(type, data)
{
    SetData(data);
    SetID(0);
    //SetStatusResponseFrameType(0);
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


    uint8_t length_msb = frame[1];
    uint8_t length_lsb = frame[2];

    unsigned int data_size = length_lsb;
    data_size |= length_msb << 8;

    uint8_t type = frame[3];

    std::vector<uint8_t> data;

    for (unsigned int byte = 4; byte < 3 + data_size; ++byte)
    {
        data.push_back(frame[byte]);
    }

    if (CompareChecksum(frame[3 + GetDataSize()]) == false)
    {
        // TODO: throw something
        std::cout << "check frame failed" << std::endl;
    }
}

Frame::Frame(const Frame& other_frame) : BeeCoLL::BaseFrame(other_frame)
{
    m_length_msb = other_frame.m_length_msb;
    m_length_lsb = other_frame.m_length_lsb;
    m_checksum = other_frame.m_checksum;
}

Frame::~Frame()
{

}

void
Frame::SetData(const std::vector<uint8_t>& data)
{
    Frame::SetData(data);
    RecalculateDataSize();
    RecalculateChecksum();
}

void
Frame::SetDataByte(unsigned int byte_index, unsigned char byte)
{
    BaseFrame::SetDataByte(byte_index, byte);
    RecalculateDataSize();
    RecalculateChecksum();
}

void
Frame::SetDataBit(unsigned int byte_index, uint8_t bit_offset, bool bit)
{
    BaseFrame::SetDataBit(byte_index, bit_offset, bit);
    RecalculateDataSize();
    RecalculateChecksum();
}

void
Frame::SetDataBit(unsigned int bit_index, bool bit)
{
    SetDataBit(bit_index / 8, bit_index % 8, bit);
}

void
Frame::InsertData(unsigned int byte_index, const std::vector<uint8_t>& data)
{
    BaseFrame::InsertData(byte_index, data);
    RecalculateDataSize();
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

/*std::vector<uint8_t>
Frame::GetFrame() const
{
    std::vector<uint8_t> frame;
    frame.push_back(START_DELIMITER);
    frame.push_back(m_length_msb);
    frame.push_back(m_length_lsb);
    frame.push_back(GetFrameType());
    std::vector<uint8_t> data = GetData();
    std::copy(data.begin(), data.end(), std::back_inserter(frame));
    frame.push_back(m_checksum);
    return frame;
}*/

void
Frame::RecalculateChecksum()
{
    //unsigned char sum = GetFrameType();
    //std::vector<uint8_t> data = GetData();
    //sum += std::accumulate(data.begin(), data.end(), 0);
    //m_checksum = 0xFF - sum;
}

void
Frame::RecalculateDataSize()
{
    uint16_t frame_data_length = 1 + GetDataSize();

    m_length_msb = frame_data_length >> 8;
    m_length_lsb = frame_data_length;
}
