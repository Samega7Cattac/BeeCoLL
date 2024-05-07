#include "beecoll/ATCommands/NI.hh"

constexpr uint8_t NI_OFFSET = 1;

BeeCoLL::Xbee::ATCommands::NI::NI() :
    ATCommand(NI_ATCOMMAND_CODE)
{

}

BeeCoLL::Xbee::ATCommands::NI::NI(const ATCommand& other) :
    ATCommand(other)
{

}

BeeCoLL::Xbee::ATCommands::NI::~NI()
{

}

std::string
BeeCoLL::Xbee::ATCommands::NI::GetNodeIdentifier()
{
    std::string value;
    uint8_t value_index = NI_OFFSET;
    char byte = 0;
    do
    {
        byte = GetByte(value_index++);
        value.push_back(byte);
    } while (byte != 0);
    value.pop_back();
    return value;
}