#ifndef BEECOLL_ATCOMMANDS_HH
#define BEECOLL_ATCOMMANDS_HH

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
#include <cstdint>
#include <string>
#include <vector>

namespace BeeCoLL
{
    enum ATCommandType : uint16_t
    {
        SL = 0x534c,
        SH = 0x5348,
        MY = 0x4d59,
        NI = 0x4e49,
        ID = 0x4944,
        OP = 0x4f50,
        CH = 0x4348,
        SC = 0x5343,

        NT = 0x4e54,
        ND = 0x4e44
    };

    class BEECOLL_API ATCommand
    {
    public:
        ATCommand(const ATCommand& other);

        virtual ~ATCommand();

        uint16_t GetATCommand() const;

        std::string GetATName() const;

        virtual void SetValue(const std::vector<uint8_t>& value = {});

        std::vector<uint8_t> GetValue() const;

    protected:
        ATCommand(uint16_t at_command, const std::string& description);

    private:
        uint16_t m_at_command;

        std::string m_name;

        std::vector<uint8_t> m_value;
    };
};

#endif // BEECOLL_ATCOMMANDS_HH