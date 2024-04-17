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
#include "ZCLAttribute.hh"
#include "ZCLPayload.hh"

namespace BeeCoLL::Zigbee
{

    class BEECOLL_API ZCLAttributeReport : public ZCLPayload
    {
        public:
            explicit ZCLAttributeReport(DataFrame& data_frame);

            ZCLAttribute GetAttribute(uint8_t attribute_index);

            uint8_t GetAttributeListSize() const;

            void UpdateAttributeListSize();


        protected:

        private:
            uint8_t m_attribute_list_size;
    };
};



#endif // BEECOLL_API_ZCL_ATTRIBUTE_REPORT_HH