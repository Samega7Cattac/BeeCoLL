#include "NT.hh"

using namespace BeeCoLL;
using namespace BeeCoLL::ATCommands;

NT::NT() :
    ATCommand(NT_ATCOMMAND_CODE)
{

}

NT::NT(const ATCommand& other) :
    ATCommand(other)
{

}

NT::~NT()
{

}
