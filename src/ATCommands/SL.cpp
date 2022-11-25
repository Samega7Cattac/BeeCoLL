#include "SL.hh"

using namespace BeeCoLL;
using namespace BeeCoLL::ATCommands;

SL::SL() :
    ATCommand(SL_ATCOMMAND_CODE)
{

}

SL::SL(const ATCommand& other) :
    ATCommand(other)
{

}

SL::~SL()
{

}
