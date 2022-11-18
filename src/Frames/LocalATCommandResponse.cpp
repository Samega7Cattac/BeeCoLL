#include "LocalATCommandResponse.hh"

using namespace BeeCoLL;
using namespace BeeCoLL::Frames;

constexpr uint8_t FRAMEID_OFFSET = 0;
constexpr uint8_t COMMAND_STATUS_OFFSET = 3;

LocalATCommandResponse::LocalATCommandResponse(const std::vector<uint8_t>& frame_data) : 
    Frame(FrameType::AT_COMMAND_RESPONSE, frame_data)
{

}

LocalATCommandResponse::LocalATCommandResponse(const Frame& other) : 
    Frame(other)
{

}

LocalATCommandResponse::~LocalATCommandResponse()
{

}

uint8_t
LocalATCommandResponse::GetFrameID()
{
    return GetDataByte(FRAMEID_OFFSET);
}

void
LocalATCommandResponse::SetFrameID(uint8_t frame_id)
{
    SetDataByte(FRAMEID_OFFSET, frame_id);
}

CommandStatus
LocalATCommandResponse::GetStatus()
{
    return static_cast<CommandStatus>(GetDataByte(COMMAND_STATUS_OFFSET));
}

void
LocalATCommandResponse::SetStatus(CommandStatus status)
{
    SetDataByte(COMMAND_STATUS_OFFSET, static_cast<uint8_t>(status));
}

std::shared_ptr<ATCommand>
LocalATCommandResponse::GetATCommand()
{
    return m_at_command;
}

void
LocalATCommandResponse::SetATCommand(const ATCommand& at_command)
{
    uint16_t at_command_code = m_at_command->GetATCommand();
    std::vector<uint8_t> data;
    // TODO: find a better way to insert an container
    // TODO: remove hardcoded frame id
    data.emplace_back(7);
    data.emplace_back(static_cast<uint8_t>(at_command_code >> 8));
    data.emplace_back(static_cast<uint8_t>(at_command_code));
    data.emplace_back(GetDataByte(COMMAND_STATUS_OFFSET));


    std::vector<uint8_t> value = m_at_command->GetValue();
    if (value.size() > 0)
    {
        data.insert(data.end(), value.begin(), value.end());
    }

    m_at_command = std::make_shared<ATCommand>(at_command);
}
