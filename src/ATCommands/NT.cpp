#include "NT.hh"

static const uint8_t NT_TIMEOUT_OFFSET = 1;

BeeCoLL::Xbee::ATCommands::NT::NT() :
    ATCommand(NT_ATCOMMAND_CODE)
{

}

BeeCoLL::Xbee::ATCommands::NT::NT(const ATCommand& other) :
    ATCommand(other)
{

}

BeeCoLL::Xbee::ATCommands::NT::~NT()
{

}

uint8_t
BeeCoLL::Xbee::ATCommands::NT::GetTimeout()
{
    return GetValue()[NT_TIMEOUT_OFFSET];
}
