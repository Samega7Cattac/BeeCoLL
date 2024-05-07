#ifndef BEECOLL_ATCOMMANDS_SL_HH
#define BEECOLL_ATCOMMANDS_SL_HH

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

constexpr uint16_t SL_ATCOMMAND_CODE = 0x534c;

namespace BeeCoLL::Xbee
{
namespace ATCommands
{
    class BEECOLL_API SL : public ATCommand
    {
    public:
        SL();
        SL(const ATCommand& other);
        ~SL();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_SL_HH