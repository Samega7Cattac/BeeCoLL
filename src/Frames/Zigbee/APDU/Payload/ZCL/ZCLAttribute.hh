#ifndef BEECOLL_API_ZIGBEE_ZCLATTRIBUTE_HH
#define BEECOLL_API_ZIGBEE_ZCLATTRIBUTE_HH


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

#include <stdint.h>
#include <vector>
#include <memory>


namespace BeeCoLL::Zigbee
{

    enum ZCLAttributeDataType : uint8_t
    {
        ZCL_DATATYPE_NULL = 0x00,
        ZCL_DATATYPE_BOOL = 0x10,
        ZCL_DATATYPE_UINT16 = 0x21,
        ZCL_DATATYPE_UINT32 = 0x23,
        ZCL_DATATYPE_INT32 = 0x2b,
        ZCL_DATATYPE_FLOAT = 0x39
    };

    class BEECOLL_API ZCLAttribute 
    {
        public:
            template<class T>
            ZCLAttribute(uint16_t attribute_id, enum ZCLAttributeDataType data_type, T value);

            ZCLAttribute(uint16_t attribute_id, enum ZCLAttributeDataType data_type);

            ZCLAttribute();

            ~ZCLAttribute();

            void SetAttributeValueVector(const std::vector<uint8_t>& attribute_value);
            
            std::vector<uint8_t> GetAttributeValueVector() const;

            uint16_t GetAttributeID() const;

            ZCLAttributeDataType GetDataType() const;
             

        private:
            enum ZCLAttributeDataType m_data_type;
            uint16_t m_attribute_id;
            std::vector<uint8_t> m_attribute_value;

    };
}




#endif // BEECOLL_API_ZIGBEE_ZCLATTRIBUTE_HH