#ifndef BEECOLL_ATCOMMANDS_ND_HH
#define BEECOLL_ATCOMMANDS_ND_HH

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
namespace  ATCommands
{
    class BEECOLL_API ND : public ATCommand
    {
    public:
        ND();
        ~ND();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_ND_HH