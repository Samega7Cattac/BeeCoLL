#include "SH.hh"

BeeCoLL::Xbee::ATCommands::SH::SH() :
    ATCommand(SH_ATCOMMAND_CODE)
{

}

BeeCoLL::Xbee::ATCommands::SH::SH(const ATCommand& other) :
    ATCommand(other)
{

}

BeeCoLL::Xbee::ATCommands::SH::~SH()
{

}
