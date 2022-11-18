#ifndef BEECOLL_FRAMES_TRANSMITREQUEST_HH
#define BEECOLL_FRAMES_TRANSMITREQUEST_HH

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

#include "Frame.hh"

#include <vector>

namespace BeeCoLL
{
namespace Frames
{
    enum TransmitOptions : uint8_t
    {
        DEFAULT_USE_TO = 0x00,
        DISABLE_ACK = 0x01,
        INDIRECT_TRANSMISSION = 0x04,
        MULTICAST = 0x08,
        SECURE_SESSION_ENCRYPTION = 0x10,
        ENABLE_APS_ENCRYPTION = 0x20,
        USE_EXTENDED_TIMEOUT = 0x40
    };

    class BEECOLL_API TransmitRequest : public Frame
    {
    public:
        explicit TransmitRequest(const std::vector<uint8_t>& frame_data = {});
        explicit TransmitRequest(const Frame& frame_data);
        ~TransmitRequest();

        uint8_t GetFrameID();

        void SetFrameID(uint8_t frame_id);

        uint64_t GetDestUniqueAddr();
        void SetDestUniqueAddr(const uint64_t& addr);

        uint16_t GetDestNetworkAddr();
        void SetDestNetworkAddr(uint16_t addr);

        std::vector<TransmitOptions> GetTransmitOptions();
        void SetTransmitOptions(const std::vector<TransmitOptions>& options);

        std::vector<uint8_t> GetPayload();
        void SetPayload(const std::vector<uint8_t>& payload);
    };
};
};

#endif // BEECOLL_FRAMES_TRANSMITREQUEST_HH