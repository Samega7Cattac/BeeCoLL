#ifndef BEECOLL_API_ZIGBEE_FRAME_HH
#define BEECOLL_API_ZIGBEE_FRAME_HH


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

// Frame Header
#include "../BaseFrame.hh"

using IEEEAddressType = uint64_t;
using AddressType = uint16_t;

namespace BeeCoLL::Zigbee
{

    enum FrameType : uint8_t
    {
        DATA_FRAME_TYPE = 0b00,
        NWK_COMMAND = 0b01,
        RESERVED = 0b10,
        INTERPAN_FRAME_TYPE = 0b11
    };

    struct FrameControl
    {
        uint8_t frame_type : 2;
        uint8_t protocol_version : 4;
        uint8_t discover_route : 2;
        bool deprecated_multicast_flag : 1;
        bool security : 1;
        bool source_route : 1;
        bool destination_ieee_address : 1;
        bool source_ieee_address : 1;
        bool end_device_initiatior : 1;
        uint8_t reserved : 2;
    };

    enum FrameOffsets
    {
        FRAME_CONTROL_OFFSET = 0,
        DESTINATION_ADDRESS_FIELD_OFFSET = 2,
        SOURCE_ADDRESS_FIELD_OFFSET = 4,
        IEEE_ADDRESS_FIELDS_OFFSET = 4,

    };

    class BEECOLL_API Frame : public BeeCoLL::BaseFrame
    {
    public:

        explicit Frame(const std::vector<uint8_t>& frame);

        Frame(const Frame& other_frame);
        
        virtual ~Frame() override;

        void SetDestinationAddress(AddressType destination_address);

        void SetSourceAddress(AddressType destination_address);
        AddressType GetSourceAddress();

        void SetDestinationIEEEAddress(IEEEAddressType destination_ieee_address);

        void SetSourceIEEEAddress(IEEEAddressType destination_ieee_address);
        IEEEAddressType GetSourceIEEEAddress();


        uint8_t GetFrameType();

        uint8_t GetStatusResponseFrameType() const;


    protected:
        explicit Frame(uint8_t frame_type);

        uint8_t GetFrameHeaderOffset() const;

        FrameControl* GetFrameControlPtr();
        const FrameControl* GetFrameControlPtr() const;

    
    };
};

#endif // BEECOLL_API_ZIGBEE_FRAME_HH