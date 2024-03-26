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

namespace BeeCoLL::Xbee
{
    class BEECOLL_API ATCommand
    {
    public:
        explicit ATCommand(uint16_t at_command);
        ATCommand(const ATCommand& other);

        virtual ~ATCommand();

        uint16_t GetATCommand() const;

        virtual void SetValue(const std::vector<uint8_t>& value = {});

        std::vector<uint8_t> GetValue() const;

    protected:
        void SetByte(unsigned int byte_index, uint8_t byte);

        uint8_t GetByte(unsigned int byte_index);

    private:
        uint16_t m_at_command;

        std::vector<uint8_t> m_value;
    };
};

#endif // BEECOLL_ATCOMMANDS_HH