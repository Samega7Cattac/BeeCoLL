#include "LocalATCommandRequest.hh"

#include <iostream>

using namespace BeeCoLL;
using namespace BeeCoLL::Frames;

constexpr uint8_t FRAMEID_OFFSET = 0;
constexpr uint8_t AT_COMMAND_MSB_OFFSET = 5;
constexpr uint8_t AT_COMMAND_LSB_OFFSET = 6;

static uint8_t frame_id = 0x01;

LocalATCommandRequest::LocalATCommandRequest(const std::vector<uint8_t>& frame_data) : 
    Frame(FrameType::AT_COMMAND, frame_data)
{
    
}

LocalATCommandRequest::LocalATCommandRequest(const Frame& other) : 
    Frame(other)
{

}

LocalATCommandRequest::~LocalATCommandRequest()
{

}

uint8_t
LocalATCommandRequest::GetFrameID()
{
    return GetDataByte(FRAMEID_OFFSET);
}

void
LocalATCommandRequest::SetFrameID(uint8_t frame_id)
{
    SetDataByte(FRAMEID_OFFSET, frame_id);
}

std::shared_ptr<ATCommand>
LocalATCommandRequest::GetATCommand()
{
    return m_at_command;
}

void
LocalATCommandRequest::SetATCommand(const ATCommand& at_command)
{
    uint16_t at_command_code = at_command.GetATCommand();
    std::vector<uint8_t> data;
    // TODO: find a better way to insert an container
    // TODO: remove hardcoded frame id
    data.emplace_back(frame_id++);
    data.emplace_back(at_command_code >> 8);
    data.emplace_back(static_cast<uint8_t>(at_command_code));

    std::vector<uint8_t> value = at_command.GetValue();
    if (value.size() > 0)
    {
        data.insert(data.end(), value.begin(), value.end());
    }
    SetData(data);

    m_at_command = std::make_shared<ATCommand>(at_command);
}
