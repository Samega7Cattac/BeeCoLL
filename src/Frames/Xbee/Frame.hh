#ifndef BEECOLL_API_XBEE_FRAME_HH
#define BEECOLL_API_XBEE_FRAME_HH


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


namespace BeeCoLL::Xbee
{

    static const uint8_t START_DELIMITER = 0x7E;

    static const uint8_t INPUT_FRAME_DELIMITER = 0x25;

    // TODO: Distribute the rest of the IDs to the corresponding frames headers
    enum FrameType : uint8_t
    {
        AT_COMMAND_QUEUE_PARAMETER_VALUE = 0x09,
        EXPLICIT_ADDRESSING_COMMAND_FRAME = 0x11,
        REMOTE_AT_COMMAND_REQUEST = 0x17,
        CREATE_SOURCE_ROUTE = 0x21,
        REGISTER_JOINING_DEVICE = 0x24,

        MODEM_STATUS = 0x8A,
        IO_DATA_SAMPLE_RX_INDICATOR = 0x92,
        XBEE_SENSOR_READ_INDICATOR = 0x94,
        NODE_IDENTIFICATION_INDICATOR = 0x95,
        REMOTE_AT_COMMAND_RESPONSE = 0x97,
        EXTENDED_MODEM_STATUS = 0x98,
        OVER_THE_AIR_FIRMWARE_UPDATE_STATUS = 0xA0,
        ROUTER_RECORD_INDICATOR = 0xA1,
        MANY_TO_ONE_ROUTE_REQUEST_INDICATOR = 0xA3,
        JOIN_NOTIFICATION_STATUS = 0xA5
    };

    class BEECOLL_API Frame : public BeeCoLL::BaseFrame
    {
    public:
        Frame(uint8_t frame_type, const std::vector<uint8_t>& data);

        Frame(const std::vector<uint8_t>& frame);

        Frame(const Frame& other_frame);
        
        virtual ~Frame() override;

        //std::vector<uint8_t> GetFrame() const override;

        uint8_t GetStatusResponseFrameType() const;

    protected:
        void SetData(const std::vector<uint8_t>& data) override;
        void SetDataByte(unsigned int byte_index, unsigned char byte) override;

        void SetDataBit(unsigned int byte_index, uint8_t bit_offset, bool bit) override;
        void SetDataBit(unsigned int bit_index, bool bit) override;

        void InsertData(unsigned int byte_index, const std::vector<uint8_t>& data) override;


        bool CompareChecksum(uint8_t other_checksum);

        void RecalculateDataSize();

    private:
        uint8_t m_length_msb;

        uint8_t m_length_lsb;

        uint8_t m_checksum;

        void RecalculateChecksum();
    };
};

#endif // BEECOLL_API_XBEE_FRAME_HH