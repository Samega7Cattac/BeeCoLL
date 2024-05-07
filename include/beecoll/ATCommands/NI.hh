#ifndef BEECOLL_ATCOMMANDS_NI_HH
#define BEECOLL_ATCOMMANDS_NI_HH

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

constexpr uint16_t NI_ATCOMMAND_CODE = 0x4e49;

namespace BeeCoLL::Xbee
{
namespace  ATCommands
{
    class BEECOLL_API NI : public ATCommand
    {
    public:
        NI();
        NI(const ATCommand& other);
        ~NI();

        std::string GetNodeIdentifier();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_NI_HH