#include "APDUFrame.hh"

// STD headers
#include <cstring>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <memory>

using namespace BeeCoLL::Zigbee;

APDUFrame::APDUFrame() : Frame(DATA_FRAME_TYPE)
{
    SetDataByte(GetFrameHeaderOffset(), 0);
}

APDUFrame::APDUFrame(uint8_t apduframe_type) : APDUFrame()
{
    SetAPDUFrameType(apduframe_type);
}



APDUFrame::APDUFrame(const std::vector<uint8_t>& frame) : Frame(frame)
{
    
}


APDUFrame::APDUFrame(const APDUFrame& other_apduframe) : 
    Frame(other_apduframe)
{
}


APDUFrame::~APDUFrame()
{

}

void
APDUFrame::SetAPDUFrameType(const uint8_t apduframe_type)
{
    GetAPDUFrameControlPtr()->apduframe_type = apduframe_type;
}



uint8_t
APDUFrame::GetAPDUFrameType()
{
    return GetAPDUFrameControlPtr()->apduframe_type;
    
}


APDUFrameControl*
APDUFrame::GetAPDUFrameControlPtr()
{
    uint8_t npdu_frame_offset = GetFrameHeaderOffset();

    return reinterpret_cast<APDUFrameControl*>(
                GetDataBytePtr(npdu_frame_offset + 
                                APDUFrameOffsets::APDUFRAME_CONTROL_OFFSET));
}
