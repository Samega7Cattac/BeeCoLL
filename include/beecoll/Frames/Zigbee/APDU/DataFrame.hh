#ifndef BEECOLL_API_ZIGBEE_DATA_FRAME_HH
#define BEECOLL_API_ZIGBEE_DATA_FRAME_HH


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

// DataFrame Header
#include "APDUFrame.hh"


namespace BeeCoLL::Zigbee
{
    class BEECOLL_API DataFrame : public APDUFrame
    {
    public:
        DataFrame();

        explicit DataFrame(const std::vector<uint8_t>& frame);
        
        DataFrame(const DataFrame& frame);

        virtual ~DataFrame() override;

        void SetProfileID(uint16_t profile_id);

        void SetClusterID(uint16_t cluster_id);

        void SetSourceEndpoint(uint8_t source_endpoint);
        uint8_t GetSourceEndpoint() const;

        void SetDestinationEndpoint(uint8_t source_endpoint);
        uint8_t GetDestinationEndpoint() const;

        void SetAPSCounter(uint8_t aps_counter);

        uint16_t GetProfileID() const;

        uint16_t GetClusterID() const;

        void SetUnicastDeliveryMode(uint8_t endpoint_address);
        void SetGroupDeliveryMode(uint16_t group_address);
        void SetBroadcastDeliveryMode();

        unsigned int GetPayloadOffset() const;

        unsigned int GetPayloadSize() const;
    protected:
        unsigned int GetDeliveryModeAddressLength() const;

        void SetPayloadOffset(unsigned int payload_offset);

        void SetPayloadSize(unsigned int payload_size);

    private:
        unsigned int m_payload_offset;

        unsigned int m_payload_size;
        unsigned int m_delivery_mode_address_length;

        void UnsetDeliveryModeAdresses();
        void SetDeliveryModeType(DeliveryType delivery_type);


    friend class ZCLPayload;
    friend class ZDOPayload;
    };
};

#endif // BEECOLL_API_ZIGBEE_DATA_FRAME_HH