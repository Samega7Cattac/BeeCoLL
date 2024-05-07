#ifndef BEECOLL_API_ZDO_SIMPLE_DESCRIPTOR_REQUEST_HH
#define BEECOLL_API_ZDO_SIMPLE_DESCRIPTOR_REQUEST_HH


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
#include "ZDOPayload.hh"

namespace BeeCoLL::Zigbee
{

    class BEECOLL_API ZDOSimpleDescriptorRequest : public ZDOPayload
    {
        public:
            explicit ZDOSimpleDescriptorRequest(DataFrame& data_frame);

            void SetTargetNetworkAddress(uint16_t network_address);
            void SetTargetEndpoint(uint8_t endpoint);

        
        protected:
        private:
    };
};



#endif // BEECOLL_API_ZDO_SIMPLE_DESCRIPTOR_REQUEST_HH