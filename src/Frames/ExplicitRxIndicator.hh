#ifndef BEECOLL_FRAMES_EXPLICITRXINDICATOR_HH
#define BEECOLL_FRAMES_EXPLICITRXINDICATOR_HH

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

// BEECOLL headers
#include "Frame.hh"

// STD headers
#include <vector>
#include <string>

namespace BeeCoLL
{
namespace Frames
{
    enum ReceiveOptions : unsigned char
    {
        PACKAGE_ACK = 0x01,
        PACKAGE_BROADCAST = 0x02,
        PACKAGE_ENCRYPTED_APS = 0x20,
        PACKAGE_EXTENDED_TIMEOUT = 0x40
    };

    class BEECOLL_API ExplicitRxIndicator : public Frame
    {
    public:
        explicit ExplicitRxIndicator(const std::vector<uint8_t>& frame_data = {});
        explicit ExplicitRxIndicator(const Frame& other);
        ~ExplicitRxIndicator();

        uint64_t GetSourceUniqueAddr();
        uint16_t GetSourceNetworkAddr();
        uint8_t GetSourceEndpoint();
        uint8_t GetDestEndpoint();
        uint16_t GetClusterID();
        uint16_t GetProfileID();
        std::vector<ReceiveOptions> GetReceiveOptions();
        std::vector<uint8_t> GetReceivedData();
        std::string GetReceivedDataToString();

    };
};
};

#endif // BEECOLL_FRAMES_EXPLICITRXINDICATOR_HH