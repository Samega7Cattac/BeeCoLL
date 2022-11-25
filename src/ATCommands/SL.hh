#ifndef BEECOLL_ATCOMMANDS_SL_HH
#define BEECOLL_ATCOMMANDS_SL_HH

#include "ATCommand.hh"

constexpr uint16_t SL_ATCOMMAND_CODE = 0x534c;

namespace BeeCoLL
{
namespace ATCommands
{
    class SL : public ATCommand
    {
    public:
        SL();
        SL(const ATCommand& other);
        ~SL();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_SL_HH