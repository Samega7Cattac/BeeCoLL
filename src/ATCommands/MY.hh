#ifndef BEECOLL_ATCOMMANDS_MY_HH
#define BEECOLL_ATCOMMANDS_MY_HH

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
    class BEECOLL_API MY : public ATCommand
    {
    public:
        MY();
        ~MY();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_MY_HH