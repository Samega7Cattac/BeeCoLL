#include "NT.hh"

static const uint8_t NT_TIMEOUT_OFFSET = 1;

BeeCoLL::ATCommands::NT::NT() :
    ATCommand(NT_ATCOMMAND_CODE)
{

}

BeeCoLL::ATCommands::NT::NT(const ATCommand& other) :
    ATCommand(other)
{

}

BeeCoLL::ATCommands::NT::~NT()
{

}

uint8_t
BeeCoLL::ATCommands::NT::GetTimeout()
{
    return GetValue()[NT_TIMEOUT_OFFSET];
}
