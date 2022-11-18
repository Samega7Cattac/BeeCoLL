#ifndef BEECOLL_FRAMES_EXTENDEDTRANSMITSTATUS_HH
#define BEECOLL_FRAMES_EXTENDEDTRANSMITSTATUS_HH

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

namespace BeeCoLL
{
namespace Frames
{
    enum DeliveryStatus : uint8_t
    {
        SUCCESS = 0x00,
        MAC_ACK_FAILURE = 0x01,
        CCA_LBT_FAILURE = 0x02,
        INDIRECT_MESSAGE_UNREQUESTED = 0x03,
        INVALID_DESTINATION_ENDPOINT = 0x15,
        NETWORK_ACK_FAILURE = 0x21,
        NOT_JOINED_TO_NETWORK = 0x22,
        SELF_ADDRESSED = 0x23,
        ADDRESS_NOT_FOUND = 0x24,
        ROUTE_NOT_FOUND = 0x25,
        BROADCAST_SOURCE_FAILED = 0x26,
        INVALID_BINDING_TABLE_INDEX = 0x2B,
        RESOURCE_ERROR = 0x2C,
        ATTEMPTED_BROADCAST_APS = 0x2D,
        ATTEMPTED_UNICAST_APS = 0x2E,
        INTERNAL_RESOURCE_ERROR = 0x31,
        RESOURCE_ERROR2 = 0x32,
        NO_SECURE_SESSION = 0x34,
        ENCRYPTION_FAILURE = 0x35,
        DATA_PAYLOAD_TOO_LARGE = 0x74,
        INDIRECT_MESSAGE_UNREQUESTED2 = 0x75
    };

    enum DiscoveryStatus : uint8_t
    {
        NO_DISCOVERY = 0x00,
        ZIGBEE_ADDRESS_DISCOVERY = 0x01,
        ROUTE_DISCOVERY = 0x02,
        ZIGBEE_AND_ROUTE_DISCOVERY = 0x03,
        ZIGBEE_END_DEVICE_EXTENDED_TIMEOUT = 0x40
    };

    class BEECOLL_API ExtendedTransmitStatus : public Frame
    {
    public:
        explicit ExtendedTransmitStatus(const std::vector<uint8_t>& frame_data = {});
        explicit ExtendedTransmitStatus(const Frame& other);
        ~ExtendedTransmitStatus();

        uint8_t GetFrameID();
        uint16_t GetDestNetworkAddr();
        uint8_t GetRetryCount();
        DeliveryStatus GetDeliveryStatus();
        DiscoveryStatus GetDiscoveryStatus();

    };
};
};

#endif // BEECOLL_FRAMES_EXTENDEDTRANSMITSTATUS_HH