#include "MY.hh"

BeeCoLL::ATCommands::MY::MY() :
    ATCommand(MY_ATCOMMAND_CODE)
{

}

BeeCoLL::ATCommands::MY::MY(const ATCommand& other) :
    ATCommand(other)
{

}

BeeCoLL::ATCommands::MY::~MY()
{

}
