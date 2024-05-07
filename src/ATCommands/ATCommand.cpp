// BEECOLL headers
#include "beecoll/ATCommands/ATCommand.hh"

// TODO Debug headers
#include <iostream>

using namespace BeeCoLL::Xbee;

ATCommand::ATCommand(uint16_t at_command) :
    m_at_command(at_command)
{

}

ATCommand::ATCommand(const ATCommand& other) :
    m_at_command(other.m_at_command),
    m_value(other.m_value)
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

void
ATCommand::SetByte(unsigned int byte_index, uint8_t byte)
{
    if (byte_index + m_value.size() > m_value.size())
    {
        // TODO: throw something
        std::cout << "get bit out of scope" << std::endl;
        m_value.resize(byte_index + m_value.size());
    }
    m_value[byte_index] = byte;
}

uint8_t
ATCommand::GetByte(unsigned int byte_index)
{
    if (byte_index >= m_value.size())
    {
        // TODO: throw something
        std::cout << "get byte out of scope" << std::endl;
    }
    return m_value[byte_index];
}
