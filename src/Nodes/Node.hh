#ifndef BEECOLL_NODE_HH
#define BEECOLL_NODE_HH

#ifdef _WIN32
    #ifdef DBRIDGEEXT_XBEE_BUILD
        #define DBRIDGEEXT_XBEE_API __declspec(dllexport)
    #else
        #define DBRIDGEEXT_XBEE_API __declspec(dllimport)
    #endif
#elif __unix__
    #ifndef DBRIDGEEXT_XBEE_API
        #define DBRIDGEEXT_XBEE_API
    #endif
#endif

// STD headers
#include <cstdint>
#include <string>

namespace DBRIDGEEXT_XBEE_API BeeCoLL
{
    //! @brief Channel Selector
    //!
    //!
    enum Channel: unsigned int
    {
        //! @brief Channel 11 (2.400 - 2.405 GHz)
        //!
        CHANNEL_11 = 0x0B,

        //! @brief Channel 12 (2.405 - 2.410 GHz)
        //!
        CHANNEL_12,

        //! @brief Channel 13 (2.410 - 2.415 GHz)
        //!
        CHANNEL_13,

        //! @brief Channel 14 (2.415 - 2.420 GHz)
        //!
        CHANNEL_14,

        //! @brief Channel 15 (2.420 - 2.425 GHz)
        //!
        CHANNEL_15,

        //! @brief Channel 16 (2.425 - 2.430 GHz)
        //!
        CHANNEL_16,

        //! @brief Channel 17 (2.430 - 2.435 GHz)
        //!
        CHANNEL_17,

        //! @brief Channel 18 (2.435 - 2.440 GHz)
        //!
        CHANNEL_18,

        //! @brief Channel 19 (2.440 - 2.445 GHz)
        //!
        CHANNEL_19,

        //! @brief Channel 20 (2.445 - 2.450 GHz)
        //!
        CHANNEL_20,

        //! @brief Channel 21 (2.450 - 2.455 GHz)
        //!
        CHANNEL_21,

        //! @brief Channel 22 (2.455 - 2.460 GHz)
        //!
        CHANNEL_22,

        //! @brief Channel 23 (2.460 - 2.465 GHz)
        //!
        CHANNEL_23,

        //! @brief Channel 24 (2.465 - 2.470 GHz)
        //!
        CHANNEL_24,

        //! @brief Channel 25 (2.470 - 2.475 GHz)
        //!
        CHANNEL_25,

        //! @brief Channel 26 (2.475 - 2.480 GHz)
        //!
        CHANNEL_26
    };

    //! @brief XBee node.
    //!
    //! Represents a XBee device.
    //!
    class Node
    {
    public:
        //! @brief Class constructor.
        //!
        Node();

        //! @brief Class destructor.
        //!
        ~Node();

        //! @brief Get Unique Address.
        //!
        //! Gets the 64-bit unique identifier of the xbee device.
        //! This value is a combination of 16-bit SH (Serial Number High) and
        //! SL (Serial Number Low).
        //!
        //! @return 64-bit unique address of the node.
        //!
        uint64_t GetUniqueAddress();

        //! @brief Get Network Address.
        //!
        //! Gets the 16-bit MY (Network Address) assigned to the xbee device
        //! by the Coordinator.
        //!
        //! @return 16-bit network address of the node.
        //!
        uint16_t GetNetworkAddress();

        //! @brief Get Node Identifier.
        //!
        //! Gets the human readable node identifier of the xbee device.
        //!
        //! @return Human readable string node identifier.
        //!
        std::string GetNodeIdentifier();

        //! @brief Get PAN ID.
        //!
        //! Gets Personal Area Network Identifier.
        //!
        //! @return 16-bit id of the PAN.
        //!
        uint16_t GetPANIdentifier();

    protected:
        void SetUniqueAddress(uint64_t new_addr);

        void SetNetworkAddr(uint16_t new_addr);

        void SetNodeIdentifier(const std::string& new_id);

        void SetPANIdentifier(uint16_t new_id);

    private:
        //! @brief Serial Number High.
        //!
        //! Most significant part of the serial number.
        //!
        uint32_t m_SH;

        //! @brief Serial Number Low.
        //!
        //! Least significant part of the Serial Number.
        //!
        uint32_t m_SL;

        //! @brief Device Network Address.
        //!
        //! Random 16-bit address that is assigned by the Coordinator when the
        //! Node joins the network.
        //!
        uint16_t m_MY;

        //! @brief Node Identifier.
        //!
        //! Human readable identifier of the xbee device.
        //!
        std::string m_NI;

        //! @brief Personal Area Network Identifier.
        //!
        //! 16-bit address that identifies the network.
        //!
        uint16_t m_ID;

        //! @brief Operating Personal Area Network Identifier.
        //!
        //! 16-bit address that identifies the operating network.
        //!
        uint16_t m_OP;

        
    };
}

#endif // BEECOLL_NODE_HH