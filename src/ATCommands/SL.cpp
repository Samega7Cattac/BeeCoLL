#include "beecoll/ATCommands/SL.hh"

BeeCoLL::Xbee::ATCommands::SL::SL() :
    ATCommand(SL_ATCOMMAND_CODE)
{

}

BeeCoLL::Xbee::ATCommands::SL::SL(const ATCommand& other) :
    ATCommand(other)
{

}

BeeCoLL::Xbee::ATCommands::SL::~SL()
{

}
