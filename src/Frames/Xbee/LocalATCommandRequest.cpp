#include "beecoll/Frames/Xbee/LocalATCommandRequest.hh"
#include "beecoll/Frames/Xbee/LocalATCommandResponse.hh"

#include <iostream>

using namespace BeeCoLL::Xbee;

constexpr uint8_t FRAMEID_OFFSET = 0;
constexpr uint8_t AT_COMMAND_MSB_OFFSET = 5;
constexpr uint8_t AT_COMMAND_LSB_OFFSET = 6;

static uint8_t frame_id = 1;

Frames::LocalATCommandRequest::LocalATCommandRequest(const std::vector<uint8_t>& frame_data) : 
    Frame(LOCAL_ATCOMMAND_REQUEST_FRAME_ID, frame_data)
{
    SetFrameID(frame_id++);
    //SetResponseTypes({LOCAL_ATCOMMAND_RESPONSE_FRAME_ID});
}

Frames::LocalATCommandRequest::LocalATCommandRequest(const Frame& other) : 
    Frame(other)
{
    
}

Frames::LocalATCommandRequest::~LocalATCommandRequest()
{

}

uint8_t
Frames::LocalATCommandRequest::GetFrameID()
{
    return GetDataByte(FRAMEID_OFFSET);
}

void
Frames::LocalATCommandRequest::SetFrameID(uint8_t frame_id)
{
    SetID(frame_id);
    SetDataByte(FRAMEID_OFFSET, frame_id);
}

std::shared_ptr<ATCommand>
Frames::LocalATCommandRequest::GetATCommand()
{
    return m_at_command;
}

void
Frames::LocalATCommandRequest::SetATCommand(const ATCommand& at_command)
{
    uint16_t at_command_code = at_command.GetATCommand();
    std::vector<uint8_t> data;
    // TODO: find a better way to insert an container
    // TODO: remove hardcoded frame id
    data.emplace_back(GetFrameID());
    data.emplace_back(at_command_code >> 8);
    data.emplace_back(static_cast<uint8_t>(at_command_code));

    std::vector<uint8_t> value = at_command.GetValue();
    if (value.size() != 0)
    {
        data.insert(data.end(), value.begin(), value.end());
    }
    SetData(data);

    m_at_command = std::make_shared<ATCommand>(at_command);
}
