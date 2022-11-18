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

namespace BeeCoLL
{
namespace ATCommands
{
    class BEECOLL_API NT : public ATCommand
    {
    public:
        NT();
        ~NT();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_NT_HH