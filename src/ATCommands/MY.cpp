#include "MY.hh"

using namespace BeeCoLL;
using namespace BeeCoLL::ATCommands;

MY::MY() :
    ATCommand(MY_ATCOMMAND_CODE)
{

}

MY::MY(const ATCommand& other) :
    ATCommand(other)
{

}

MY::~MY()
{

}
