#ifndef BEECOLL_API_ZIGBEE_APDUFRAME_HH
#define BEECOLL_API_ZIGBEE_APDUFRAME_HH


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

// STD headers
#include <vector>
#include <cstdint>

// APDUFrame Header
#include "../Frame.hh"


namespace BeeCoLL::Zigbee
{
    enum APDUFrameType : uint8_t
    {
        DATA_APDUFRAME_TYPE = 0b00,
        ACK_APDUFRAME_TYPE = 0b01,
        COMMAND_APDUFRAME_TYPE = 0b10,
        INTERPAN_APDUFRAME_TYPE = 0b11
    };

    enum DeliveryType : uint8_t
    {
        NULL_DELIVERY_MODE = 0b10, // Internal online, reserved in the Zigbee Specification
        UNICAST_DELIVERY_MODE = 0b00,
        BROADCAST_DELIVERY_MODE = 0b10,
        GROUP_DELIVERY_MODE = 0b11
    };

    struct APDUFrameControl
    {
        uint8_t apduframe_type : 2;
        uint8_t delivery_type : 2 = DeliveryType::UNICAST_DELIVERY_MODE;
        bool ack_format : 1;
        bool security : 1;
        bool ack_request : 1;
        bool extended_header_present : 1;
    };

    enum APDUFrameOffsets
    {
        APDUFRAME_CONTROL_OFFSET = 0,
        DELIVERY_ADDRESS_FIELD_OFFSET = 1
    };

    class BEECOLL_API APDUFrame : public BeeCoLL::Zigbee::Frame
    {
    public:
        APDUFrame();

        explicit APDUFrame(const std::vector<uint8_t>& apduframe);

        APDUFrame(const APDUFrame& other_apduframe);
        
        virtual ~APDUFrame() override;

        void SetAPDUFrameType(const uint8_t apduframe_type);

        uint8_t GetAPDUFrameType();

        uint8_t GetStatusResponseAPDUFrameType() const;


    protected:
        explicit APDUFrame(uint8_t apduframe_type);

        APDUFrameControl* GetAPDUFrameControlPtr();
    };
};

#endif // BEECOLL_API_ZIGBEE_APDUFRAME_HH