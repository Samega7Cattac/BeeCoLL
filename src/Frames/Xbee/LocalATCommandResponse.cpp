#include "LocalATCommandResponse.hh"

using namespace BeeCoLL::Xbee;

constexpr uint8_t FRAMEID_OFFSET = 0;
constexpr uint8_t ATCOMMAND_OFFSET1 = 1;
constexpr uint8_t ATCOMMAND_OFFSET2 = 2;
constexpr uint8_t COMMAND_STATUS_OFFSET = 3;

Frames::LocalATCommandResponse::LocalATCommandResponse(const std::vector<uint8_t>& frame_data) : 
    Frame(LOCAL_ATCOMMAND_RESPONSE_FRAME_ID, frame_data),
    m_at_command(0)
{
    SetID(GetFrameID());
    GenerateATCommand();
}

Frames::LocalATCommandResponse::LocalATCommandResponse(const Frame& other) : 
    Frame(other),
    m_at_command(0)
{
    SetID(GetFrameID());
    GenerateATCommand();
}

Frames::LocalATCommandResponse::~LocalATCommandResponse()
{
    
}

uint8_t
Frames::LocalATCommandResponse::GetFrameID()
{
    return GetDataByte(FRAMEID_OFFSET);
}

void
Frames::LocalATCommandResponse::SetFrameID(uint8_t frame_id)
{
    SetID(frame_id);
    SetDataByte(FRAMEID_OFFSET, frame_id);
}

Frames::CommandStatus
Frames::LocalATCommandResponse::GetStatus()
{
    return static_cast<CommandStatus>(GetDataByte(COMMAND_STATUS_OFFSET));
}

void
Frames::LocalATCommandResponse::SetStatus(CommandStatus status)
{
    SetDataByte(COMMAND_STATUS_OFFSET, static_cast<uint8_t>(status));
}

ATCommand
Frames::LocalATCommandResponse::GetATCommand()
{
    return m_at_command;
}

void
Frames::LocalATCommandResponse::SetATCommand(const ATCommand& at_command)
{
    uint16_t at_command_code = m_at_command.GetATCommand();
    std::vector<uint8_t> data;
    // TODO: find a better way to insert an container
    // TODO: remove hardcoded frame id
    data.emplace_back(7);
    data.emplace_back(static_cast<uint8_t>(at_command_code >> 8));
    data.emplace_back(static_cast<uint8_t>(at_command_code));
    data.emplace_back(GetDataByte(COMMAND_STATUS_OFFSET));


    std::vector<uint8_t> value = m_at_command.GetValue();
    if (value.size() > 0)
    {
        data.insert(data.end(), value.begin(), value.end());
    }

    m_at_command = at_command;
}

void
Frames::LocalATCommandResponse::GenerateATCommand()
{
    uint16_t at_code = GetDataByte(ATCOMMAND_OFFSET2);
    at_code |= static_cast<uint16_t>(GetDataByte(ATCOMMAND_OFFSET1)) << 8;
    ATCommand at_cmd(at_code);
    m_at_command = at_cmd;
    std::vector<uint8_t> data = GetData();
    data.erase(data.begin(), data.begin() + 4);
    m_at_command.SetValue(data);
}
