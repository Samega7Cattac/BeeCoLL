#ifndef BEECOLL_HH
#define BEECOLL_HH

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

// BeeCoLL headers
#include "Frames/Frame.hh"
#include "Node.hh"
#include "SerialInterface.hh"

// STD headers
#include <string>
#include <bitset>

namespace BeeCoLL
{
    constexpr const std::size_t N_SUPPORTED_CHANNELS = 16;

    enum XBEE_SPECIAL_MAC_ADDR : uint64_t
    {
        XBEE_SH_ID = 0x0013A20000000000,
        BROADCAST = 0x000000000000FFFF
    };

    enum XBEE_SPECIAL_MY_ADDR : uint16_t
    {
        COORDINATOR = 0x0000,
        NOT_CONNECTED = 0xFFFE
    };

    //! @brief zigbee network cordinator.
    //! 
    //! Contain function which can onlu 
    //!
    class BEECOLL_API Coordinator : public Node, public SerialInterface
    {
    public:

        explicit Coordinator(const std::string& serial_device_path);

        ~Coordinator();

        void SendAPICommand(FrameType function, const std::vector<uint8_t>& data);

        void SendAPICommand(const Frame& frame);

        Frame ReceiveAPICommand();

        void StartDiscover();
    };
}
#endif // BEECOLL_HH