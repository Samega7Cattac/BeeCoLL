#ifndef BEECOLL_FRAMES_RECIEVEPACKET_HH
#define BEECOLL_FRAMES_RECIEVEPACKET_HH

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
#include "ExplicitRxIndicator.hh"

// STD headers
#include <vector>
#include <string>

namespace BeeCoLL
{
namespace Frames
{
    constexpr uint8_t RECEIVE_PACKET_FRAME_ID = 0x90;

    class BEECOLL_API RecievePacket : public Frame
    {
    public:
        explicit RecievePacket(const std::vector<uint8_t>& frame_data = {});
        explicit RecievePacket(const Frame& other);
        ~RecievePacket();

        uint64_t GetSourceUniqueAddr();
        uint16_t GetSourceNetworkAddr();
        std::vector<ReceiveOptions> GetReceiveOptions();
        std::vector<uint8_t> GetReceivedData();
        std::string GetReceivedDataToString();
    };
};
};

#endif // BEECOLL_FRAMES_RECIEVEPACKET_HH