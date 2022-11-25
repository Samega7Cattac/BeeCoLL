#ifndef BEECOLL_ATCOMMANDS_NT_HH
#define BEECOLL_ATCOMMANDS_NT_HH

#include "ATCommand.hh"

constexpr uint16_t NT_ATCOMMAND_CODE = 0x4e54;

namespace BeeCoLL
{
namespace ATCommands
{
    class NT : public ATCommand
    {
    public:
        NT();
        NT(const ATCommand& other);
        ~NT();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_NT_HH