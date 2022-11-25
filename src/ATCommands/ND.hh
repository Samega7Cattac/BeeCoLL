#ifndef BEECOLL_ATCOMMANDS_ND_HH
#define BEECOLL_ATCOMMANDS_ND_HH

#include "ATCommand.hh"

constexpr uint16_t ND_ATCOMMAND_CODE = 0x4e44;

namespace BeeCoLL
{
namespace ATCommands
{
    class ND : public ATCommand
    {
    public:
        ND();
        ND(const ATCommand& other);
        ~ND();

        uint16_t GetMY();
        uint32_t GetSH();
        uint32_t GetSL();
        // uint8_t GetDB();
        std::string GetNI();
        uint16_t GetParentNetworkAddr();
        uint8_t GetDeviceType();
        uint8_t GetStatus();
        uint16_t GetProfileID();
        uint16_t GetManufactureID();
        uint32_t GetDigiDeviceType();
        uint8_t GetRssiOfLastHop();
    };
};
};

#endif // BEECOLL_ATCOMMANDS_ND_HH