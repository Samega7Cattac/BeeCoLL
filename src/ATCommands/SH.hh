#ifndef BEECOLL_ATCOMMANDS_SH_HH
#define BEECOLL_ATCOMMANDS_SH_HH

#include "ATCommand.hh"

constexpr uint16_t SH_ATCOMMAND_CODE = 0x5348;

namespace BeeCoLL
{
namespace ATCommands
{
    class SH : public ATCommand
    {
    public:
        SH();
        SH(const ATCommand& other);
        ~SH();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_SH_HH