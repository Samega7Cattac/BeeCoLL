#ifndef BEECOLL_API_ZDO_DEVICE_ANNOUNCE_HH
#define BEECOLL_API_ZDO_DEVICE_ANNOUNCE_HH


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

    struct ZDODeviceAnnounceFields
    {
        uint16_t network_address;
        uint64_t ieee_address;
        uint8_t device_capability;
    };

    class BEECOLL_API ZDODeviceAnnounce : public ZDOPayload
    {
        public:
            explicit ZDODeviceAnnounce(DataFrame& data_frame);
            ~ZDODeviceAnnounce();

            uint16_t GetNetworkAddress();
            uint64_t GetIEEEAddress();

        protected:
            const ZDODeviceAnnounceFields* GetZDODeviceAnnouncePtr() const;

            uint8_t GetZDODeviceAnnounceOffset() const;
        private:
    };
};



#endif // BEECOLL_API_ZDO_DEVICE_ANNOUNCE_HH