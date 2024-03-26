#include "MY.hh"

BeeCoLL::Xbee::ATCommands::MY::MY() :
    ATCommand(MY_ATCOMMAND_CODE)
{

}

BeeCoLL::Xbee::ATCommands::MY::MY(const ATCommand& other) :
    ATCommand(other)
{

}

BeeCoLL::Xbee::ATCommands::MY::~MY()
{

}
