#ifndef BEECOLL_SERIAL_NODE_HH
#define BEECOLL_SERIAL_NODE_HH

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
#include <string>
#include <vector>

namespace BeeCoLL
{
    class BEECOLL_API SerialInterface
    {
    public:
        explicit SerialInterface(const std::string& serial_device);
        ~SerialInterface();

    protected:
        void WriteToSerial(const std::vector<uint8_t>& data);
        std::vector<uint8_t> ReadFromSerial(const std::size_t& read_n_bytes);

    private:
        int m_serial_fd;
    };
};

#endif // BEECOLL_SERIAL_NODE_HH