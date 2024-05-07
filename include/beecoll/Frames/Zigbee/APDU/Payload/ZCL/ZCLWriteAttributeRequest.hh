#ifndef BEECOLL_API_ZCL_WRITE_ATTRIBUTE_REQUEST_HH
#define BEECOLL_API_ZCL_WRITE_ATTRIBUTE_REQUEST_HH


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

    class BEECOLL_API ZCLWriteAttributeRequest : public ZCLPayload
    {
        public:
            explicit ZCLWriteAttributeRequest(DataFrame& data_frame);
        
            void AddAttributeToRequest(uint16_t attribute_identifier,
                                     uint8_t attribute_data_type,
                                     const std::vector<uint8_t>& attribute_value);
        
        protected:

        private:
    };
};



#endif // BEECOLL_API_ZCL_WRITE_ATTRIBUTE_REQUEST_HH