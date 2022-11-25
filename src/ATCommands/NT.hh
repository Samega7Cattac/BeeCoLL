#ifndef BEECOLL_ATCOMMANDS_NT_HH
#define BEECOLL_ATCOMMANDS_NT_HH

#ifdef _WIN32
    #ifdef BEECOLL_BUILD
        #define BEECOLL_API __declspec(dllexport)
    #else
        #define BEECOLL_API __declspec(dllimport)
    #endif
#elif __unix__
    #ifndef BEECOLL_API
        #define BEECOLL_API
    #endif
#endif

#include "ATCommand.hh"

constexpr uint16_t NT_ATCOMMAND_CODE = 0x4e54;

namespace BeeCoLL
{
namespace ATCommands
{
    class BEECOLL_API NT : public ATCommand
    {
    public:
        NT();
        NT(const ATCommand& other);
        ~NT();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_NT_HH