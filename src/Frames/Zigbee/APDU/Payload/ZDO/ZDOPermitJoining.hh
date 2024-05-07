#ifndef BEECOLL_API_ZDO_PERMIT_JOINING_HH
#define BEECOLL_API_ZDO_PERMIT_JOINING_HH


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

    class BEECOLL_API ZDOPermitJoining : public ZDOPayload
    {
        public:
            explicit ZDOPermitJoining(DataFrame& data_frame);

            void SetPermitDuration(uint8_t endpoint);

        
        protected:
        private:
    };
};



#endif // BEECOLL_API_ZDO_PERMIT_JOINING_HH