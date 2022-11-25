#ifndef BEECOLL_API_FRAME_HH
#define BEECOLL_API_FRAME_HH


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

static const uint8_t START_DELIMITER = 0x7E;

static const uint8_t INPUT_FRAME_DELIMITER = 0x25;

namespace BeeCoLL
{
    enum FrameType : uint8_t
    {
        AT_COMMAND = 0x08,
        AT_COMMAND_QUEUE_PARAMETER_VALUE = 0x09,
        TRANSMIT_REQUEST = 0x10,
        EXPLICIT_ADDRESSING_COMMAND_FRAME = 0x11,
        REMOTE_AT_COMMAND_REQUEST = 0x17,
        CREATE_SOURCE_ROUTE = 0x21,
        REGISTER_JOINING_DEVICE = 0x24,

        AT_COMMAND_RESPONSE = 0x88,
        MODEM_STATUS = 0x8A,
        TRANSMIT_STATUS = 0x8B,
        RECEIVE_PACKET = 0x90,
        EXPLICIT_RX_INDICATOR = 0x91,
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

    class BEECOLL_API Frame
    {
    public:
        Frame(FrameType type, const std::vector<uint8_t>& data);

        explicit Frame(const std::vector<uint8_t>& frame);

        Frame(const Frame& other_frame);
        
        virtual ~Frame();

        FrameType GetType() const;

        std::vector<uint8_t> GetFrame() const;

        uint8_t GetID() const;

        std::vector<uint8_t> GetResponseTypes() const;

    protected:
        std::vector<uint8_t> GetData();
        void SetData(const std::vector<uint8_t>& data);
        uint8_t GetDataByte(unsigned int byte_index);
        void SetDataByte(unsigned int byte_index, unsigned char byte);

        bool GetDataBit(unsigned int byte_index, uint8_t bit_offset);
        bool GetDataBit(unsigned int bit_index);
        void SetDataBit(unsigned int byte_index, uint8_t bit_offset, bool bit);
        void SetDataBit(unsigned int bit_index, bool bit);

        bool GetDataBitMask(unsigned int byte_index, uint8_t mask);

        void InsertDataAT(unsigned int byte_index, const std::vector<uint8_t>& data);

        void SetType(FrameType type);

        bool CompareChecksum(uint8_t other_checksum);

        void SetID(uint8_t id);

        void SetResponseTypes(const std::vector<uint8_t>& response_types);

    private:
        std::vector<uint8_t> m_response_types;

        uint8_t m_id;

        uint8_t m_length_msb;

        uint8_t m_length_lsb;

        FrameType m_type;

        std::vector<uint8_t> m_data;

        uint8_t m_checksum;

        void RecalculateChecksum();
        
        void RecalculateDataSize();
    };
};

#endif // BEECOLL_FRAME_HH