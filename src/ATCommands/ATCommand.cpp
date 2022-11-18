#include "ATCommand.hh"

using namespace BeeCoLL;

ATCommand::ATCommand(const ATCommand& other) :
    m_at_command(other.m_at_command),
    m_name(other.m_name)
{

}

ATCommand::~ATCommand()
{

}

uint16_t
ATCommand::GetATCommand() const
{
    return m_at_command;
}

std::string
ATCommand::GetATName() const
{
    return m_name;
}

void
ATCommand::SetValue(const std::vector<uint8_t>& data)
{
    if (data.size() == 0)
    {
        m_value.clear();
        return;
    }
    m_value = data;
}

std::vector<uint8_t>
ATCommand::GetValue() const
{
    return m_value;
}

ATCommand::ATCommand(uint16_t at_command, const std::string& name) :
    m_at_command(at_command),
    m_name(name)
{

}
