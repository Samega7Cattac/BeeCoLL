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

    enum ZDOSimpleDescriptorStatus : uint8_t
    {
        SUCCESS,
        INVALID_EP,
        NOT_ACTIVE,
        DEVICE_NOT_FOUND,
        INV_REQUESTTYPE,
        NO_DESCRIPTOR
    };

    struct ZDOSimpleDescriptorStaticFields
    {
        enum ZDOSimpleDescriptorStatus status;
        uint16_t target_network_address;
        uint8_t simple_descriptor_length;
        uint8_t endpoint;
        uint16_t profile_id;
        uint16_t device_id;
        uint8_t device_version : 4;
        uint8_t reserved : 4;
    };

    class BEECOLL_API ZDOSimpleDescriptorResponse : public ZDOPayload
    {
        public:
            explicit ZDOSimpleDescriptorResponse(DataFrame& data_frame);

            enum ZDOSimpleDescriptorStatus GetSimpleDescriptorStatus() const;

            uint16_t GetTargetNetworkAddress() const;

            uint8_t GetSimpleDescriptorLength() const;

            uint8_t GetEndpoint() const;

            uint16_t GetProfileID() const;

            uint16_t GetDeviceID() const;

            uint8_t GetInputClusterCount() const;
            uint16_t GetInputCluster(uint8_t input_cluster_index) const;

            uint8_t GetOutputClusterCount() const;
            uint16_t GetOutputCluster(uint8_t output_cluster_index) const;
        
        protected:
            ZDOSimpleDescriptorStaticFields* GetZDOSimpleDescriptorStaticFieldsPtr();
            const ZDOSimpleDescriptorStaticFields* GetZDOSimpleDescriptorStaticFieldsPtr() const;

            uint8_t GetZDOSimpleDescriptorOffset() const;
        private:
    };
};



#endif // BEECOLL_API_ZDO_SIMPLE_DESCRIPTOR_RESPONSE_HH