#ifndef BEECOLL_API_ZCL_PAYLOAD_TYPE_HH
#define BEECOLL_API_ZCL_PAYLOAD_TYPE_HH


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

// STD includes
#include <vector>
#include <cstdint>

// BeeCoLL includes
#include "../../DataFrame.hh"

namespace BeeCoLL::Zigbee
{

    enum ZCLPayloadType : uint8_t
    {
        IMPLEMENTATION_SPECIFIC_CLUSTER_COMMAND = 0b00,
        GLOBAL_CLUSTER_COMMAND = 0b01
    };

    enum ZCLDirection : bool
    {
        SERVER_TO_CLIENT = true,
        CLIENT_TO_SERVER = false
    };

    struct ZCLPayloadControl
    {
        uint8_t payload_type : 2;
        bool manufacturer_specific : 1;
        bool direction : 1;
        bool disable_default_response : 1;
        uint8_t reserved : 2;
    };

    class BEECOLL_API ZCLPayload
    {
        public:
            static uint8_t GetZCLPayloadCommandIdentifier(DataFrame& data_frame);

            void SetManufacturerCode(uint16_t manufacturer_code);

            uint8_t GetPayloadOffset();
            uint8_t GetPayloadSize();

            bool IsManufacturerSpecific();

        protected:
            explicit ZCLPayload(DataFrame& data_frame, uint8_t command_identifier);

            ZCLPayloadControl* GetPayloadControlPtr();

            void InsertData(unsigned int byte_index, const std::vector<uint8_t>& data);

            uint8_t GetDataByte(unsigned int byte_offset);
            std::vector<uint8_t>& GetData();

            DataFrame& m_data_frame;
        private:
    
    };
};



#endif // BEECOLL_API_ZCL_PAYLOAD_TYPE_HH