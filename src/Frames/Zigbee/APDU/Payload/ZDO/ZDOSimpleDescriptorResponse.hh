#ifndef BEECOLL_API_ZDO_SIMPLE_DESCRIPTOR_RESPONSE_HH
#define BEECOLL_API_ZDO_SIMPLE_DESCRIPTOR_RESPONSE_HH


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

    struct ZDOSimpleDescriptorStaticFields
    {
        uint8_t endpoint;
        uint16_t profile_id;
        uint16_t device_id;
    };

    class BEECOLL_API ZDOSimpleDescriptorResponse : public ZDOPayload
    {
        public:
            explicit ZDOSimpleDescriptorResponse(DataFrame& data_frame);

            uint8_t GetEndpoint();

            uint16_t GetProfileID();

            uint16_t GetDeviceID();

            uint8_t GetInputClusterCount();
            uint16_t GetInputCluster(uint8_t input_cluster_index);

            uint8_t GetOutputClusterCount();
            uint16_t GetOutputCluster(uint8_t output_cluster_index);
        
        protected:
            ZDOSimpleDescriptorStaticFields* GetZDOSimpleDescriptorStaticFieldsPtr();

            uint8_t GetZDOSimpleDescriptorOffset();
        private:
    };
};



#endif // BEECOLL_API_ZDO_SIMPLE_DESCRIPTOR_RESPONSE_HH