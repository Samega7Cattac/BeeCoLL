#ifndef BEECOLL_API_ZCL_ATTRIBUTE_REPORT_HH
#define BEECOLL_API_ZCL_ATTRIBUTE_REPORT_HH


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
#include "ZCLPayload.hh"

namespace BeeCoLL::Zigbee
{

    enum ZCLAttributeDataType
    {
        ZCL_DATATYPE_NULL = 0x00,
        ZCL_DATATYPE_UINT16 = 0x21,
        ZCL_DATATYPE_INT32 = 0x2b,
        ZCL_DATATYPE_FLOAT = 0x39
    };

    class BEECOLL_API ZCLAttributeReport : public ZCLPayload
    {
        public:
            explicit ZCLAttributeReport(DataFrame& data_frame);
        
            struct Attribute
            {
                enum ZCLAttributeDataType data_type;
                uint16_t attribute_id;
                std::vector<uint8_t> attribute_value;
            };

            Attribute GetAttribute(uint8_t attribute_index);

            uint8_t GetAttributeListSize() const;

            void UpdateAttributeListSize();


        protected:

        private:
            uint8_t m_attribute_list_size;
    };
};



#endif // BEECOLL_API_ZCL_ATTRIBUTE_REPORT_HH