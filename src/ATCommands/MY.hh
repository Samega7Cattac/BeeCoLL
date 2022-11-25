#ifndef BEECOLL_ATCOMMANDS_MY_HH
#define BEECOLL_ATCOMMANDS_MY_HH

#include "ATCommand.hh"

constexpr uint16_t MY_ATCOMMAND_CODE = 0x4d59;

namespace BeeCoLL
{
namespace ATCommands
{
    class MY : public ATCommand
    {
    public:
        MY();
        MY(const ATCommand& other);
        ~MY();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_MY_HH