#include "SH.hh"

using namespace BeeCoLL;
using namespace BeeCoLL::ATCommands;

SH::SH() :
    ATCommand(SH_ATCOMMAND_CODE)
{

}

SH::SH(const ATCommand& other) :
    ATCommand(other)
{

}

SH::~SH()
{

}
