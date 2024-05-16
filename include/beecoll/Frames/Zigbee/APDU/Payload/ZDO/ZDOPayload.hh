#ifndef BEECOLL_API_ZDO_PAYLOAD_HH
#define BEECOLL_API_ZDO_PAYLOAD_HH


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

//BeeCoLL includes
#include "../../DataFrame.hh"

namespace BeeCoLL::Zigbee
{

    enum ZDOCommandClusterID : uint16_t
    {
	    ZDO_COMMAND_SIMPLE_DESCRIPTOR_REQUEST = 0x0004,
	    ZDO_COMMAND_SIMPLE_DESCRIPTOR_RESPONSE = 0x8004,
	    ZDO_COMMAND_DEVICE_ANNOUNCE = 0x0013
    };

    class BEECOLL_API ZDOPayload
    {
        public:
            uint8_t GetPayloadOffset();
            uint8_t GetPayloadSize();

        protected:
            explicit ZDOPayload(DataFrame& data_frame);

            //ZCLPayloadControl* GetPayloadControlPtr();

            void InsertData(unsigned int byte_index, const std::vector<uint8_t>& data);

            void SetDataByte(unsigned int byte_offset, uint8_t byte);
            uint8_t GetDataByte(unsigned int byte_offset) const;

            std::vector<uint8_t>& GetData();
            std::vector<uint8_t>& GetData() const;

            DataFrame& m_data_frame;
        private:
    
    };
};



#endif // BEECOLL_API_ZDO_PAYLOAD_HH