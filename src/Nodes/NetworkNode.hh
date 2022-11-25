#ifndef BEECOLL_NODE_NETWORKNODE_HH
#define BEECOLL_NODE_NETWORKNODE_HH

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

// BEECOLL headers
#include "Node.hh"
#include "Coordinator.hh"

// STD headers
#include <functional>

namespace BeeCoLL
{
    struct NetworkNodeInfo
    {
        uint16_t MY;
        uint32_t SH;
        uint32_t SL;
        // TODO: DB not not he frame?????
        uint8_t DB;
        std::string NI;
        uint16_t parent_network_addr;
        uint8_t node_type;
        uint8_t status;
        uint16_t profile_id;
        uint16_t manufacture_id;

        // Optional
        uint32_t digi_device_type;
        uint32_t rssi_of_last_hop;
    };

    class BEECOLL_API NetworkNode : public Node
    {
    public:
        NetworkNode(const NetworkNodeInfo& node_info,
                    class Coordinator* coordinator);
        NetworkNode(const NetworkNode& other);
        ~NetworkNode();

        void SetCallback(const std::function<void(const Frame&)>& callback);
        void TriggerCallback(const Frame& frame);

    private:
        NetworkNodeInfo m_info;

        class Coordinator* m_coordinator;

        std::function<void(const Frame&)> m_callback;
    };
};

#endif // BEECOLL_NODE_NETWORKNODE_HH