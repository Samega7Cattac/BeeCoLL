#ifndef BEECOLL_ATCOMMANDS_SH_HH
#define BEECOLL_ATCOMMANDS_SH_HH

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
namespace BEECOLL_API ATCommands
{
    class SH : public ATCommand
    {
    public:
        SH();
        
        ~SH();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_SH_HH