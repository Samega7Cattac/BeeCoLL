#include "ND.hh"

constexpr uint8_t MY_OFFSET1 = 1;
constexpr uint8_t MY_OFFSET2 = 0;
constexpr uint8_t SH_OFFSET1 = 5;
constexpr uint8_t SH_OFFSET2 = 4;
constexpr uint8_t SH_OFFSET3 = 3;
constexpr uint8_t SH_OFFSET4 = 2;
constexpr uint8_t SL_OFFSET1 = 9;
constexpr uint8_t SL_OFFSET2 = 8;
constexpr uint8_t SL_OFFSET3 = 7;
constexpr uint8_t SL_OFFSET4 = 6;
constexpr uint8_t NI_OFFSET = 10;

constexpr uint8_t PARENT_NETWORK_ADDRESS_OFFSET1 = 12;
constexpr uint8_t PARENT_NETWORK_ADDRESS_OFFSET2 = 11;
constexpr uint8_t DEVICE_TYPE_OFFSET = 13;
constexpr uint8_t STATUS_OFFSET = 14;
constexpr uint8_t PROFILE_ID_OFFSET1 = 16;
constexpr uint8_t PROFILE_ID_OFFSET2 = 15;
constexpr uint8_t MANUFACTURE_ID_OFFSET1 = 18;
constexpr uint8_t MANUFACTURE_ID_OFFSET2 = 17;
constexpr uint8_t DIGI_DEVICE_TYPE_OFFSET1 = 22;
constexpr uint8_t DIGI_DEVICE_TYPE_OFFSET2 = 21;
constexpr uint8_t DIGI_DEVICE_TYPE_OFFSET3 = 20;
constexpr uint8_t DIGI_DEVICE_TYPE_OFFSET4 = 19;
constexpr uint8_t RSSI_OF_LAST_HOP_OFFSET = 23;

BeeCoLL::Xbee::ATCommands::ND::ND() :
    ATCommand(ND_ATCOMMAND_CODE)
{

}

BeeCoLL::Xbee::ATCommands::ND::ND(const ATCommand& other) :
    ATCommand(other)
{

}

BeeCoLL::Xbee::ATCommands::ND::~ND()
{

}

uint16_t
BeeCoLL::Xbee::ATCommands::ND::GetMY()
{
    uint16_t value;
    value = GetByte(MY_OFFSET1);
    value |= static_cast<uint16_t>(GetByte(MY_OFFSET2)) << 8;
    return value;
}

uint32_t
BeeCoLL::Xbee::ATCommands::ND::GetSH()
{
    uint32_t value;
    value = GetByte(SH_OFFSET1);
    value |= static_cast<uint16_t>(GetByte(SH_OFFSET2)) << 8;
    value |= static_cast<uint32_t>(GetByte(SH_OFFSET3)) << 16;
    value |= static_cast<uint32_t>(GetByte(SH_OFFSET4)) << 24;
    return value;
}

uint32_t
BeeCoLL::Xbee::ATCommands::ND::GetSL()
{
    uint32_t value;
    value = GetByte(SL_OFFSET1);
    value |= static_cast<uint16_t>(GetByte(SL_OFFSET2)) << 8;
    value |= static_cast<uint32_t>(GetByte(SL_OFFSET3)) << 16;
    value |= static_cast<uint32_t>(GetByte(SL_OFFSET4)) << 24;
    return value;
}

std::string
BeeCoLL::Xbee::ATCommands::ND::GetNI()
{
    std::string value;
    uint8_t value_index = NI_OFFSET; 
    char byte = 0;
    do
    {
        byte = GetByte(value_index++);
        value.push_back(byte);
    } while (byte != 0);
    value.pop_back();
    return value;
}

uint16_t
BeeCoLL::Xbee::ATCommands::ND::GetParentNetworkAddr()
{
    // Start of NI + size of NI + last 0
    uint8_t ni_size = GetNI().length();

    uint16_t value;
    value = GetByte(ni_size + PARENT_NETWORK_ADDRESS_OFFSET1);
    value |= static_cast<uint16_t>(GetByte(ni_size + PARENT_NETWORK_ADDRESS_OFFSET2)) << 8;
    return value;
}

uint8_t
BeeCoLL::Xbee::ATCommands::ND::GetDeviceType()
{
    // Start of NI + size of NI + last 0
    uint8_t ni_si = GetNI().length();
    return GetByte(ni_si + DEVICE_TYPE_OFFSET);
}

uint8_t
BeeCoLL::Xbee::ATCommands::ND::GetStatus()
{
    // Start of NI + size of NI + last 0
    uint8_t ni_size = GetNI().length();
    return GetByte(ni_size + STATUS_OFFSET);
}

uint16_t
BeeCoLL::Xbee::ATCommands::ND::GetProfileID()
{
    // Start of NI + size of NI + last 0
    uint8_t ni_size = GetNI().length();

    uint16_t value;
    value = GetByte(ni_size + PROFILE_ID_OFFSET1);
    value |= static_cast<uint16_t>(GetByte(ni_size + PROFILE_ID_OFFSET2)) << 8;
    return value;
}

uint16_t
BeeCoLL::Xbee::ATCommands::ND::GetManufactureID()
{
    // Start of NI + size of NI + last 0
    uint8_t ni_size = GetNI().length();

    uint16_t value;
    value = GetByte(ni_size + MANUFACTURE_ID_OFFSET1);
    value |= static_cast<uint16_t>(GetByte(ni_size + MANUFACTURE_ID_OFFSET2)) << 8;
    return value;
}

uint32_t
BeeCoLL::Xbee::ATCommands::ND::GetDigiDeviceType()
{
    // Start of NI + size of NI + last 0
    uint8_t ni_size = GetNI().length();

    uint32_t value;
    value = GetByte(ni_size + DIGI_DEVICE_TYPE_OFFSET1);
    value |= static_cast<uint16_t>(GetByte(ni_size + DIGI_DEVICE_TYPE_OFFSET2)) << 8;
    value |= static_cast<uint32_t>(GetByte(ni_size + DIGI_DEVICE_TYPE_OFFSET3)) << 16;
    value |= static_cast<uint32_t>(GetByte(ni_size + DIGI_DEVICE_TYPE_OFFSET4)) << 24;
    return value;
}

uint8_t
BeeCoLL::Xbee::ATCommands::ND::GetRssiOfLastHop()
{
    // Start of NI + size of NI + last 0
    uint8_t ni_size = GetNI().length();
    return GetByte(ni_size + RSSI_OF_LAST_HOP_OFFSET);
}
