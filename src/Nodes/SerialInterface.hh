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
#include <termios.h>

namespace BeeCoLL
{
    class BEECOLL_API SerialInterface
    {
    public:
        virtual ~SerialInterface();

    protected:
        explicit SerialInterface(int serial_fd);
        explicit SerialInterface(const std::string& serial_device);

        int GetSerialFD() const;

        void WriteToSerial(const std::vector<uint8_t>& data);
        std::vector<uint8_t> ReadFromSerial(std::size_t read_n_bytes);

        void LockFD(int fd);

        void ClearSerial();

        void SetParityBit(bool enable);

        void SetStopBits(bool enable);

        void SetBitsInByte(uint8_t bits);

        void SetControlFlow(bool enable);

        void SetModemLine(bool enable);

        void SetCanonicalMode(bool enable);

        void SetEcho(bool enable);

        void SetSignalChars(bool enable);

        void SetSoftwareFlowControl(bool enable);

        void SetOutputSpecialChars(bool enable);

        void SetInputSpecialChars(bool enable);

        void SetTimeoutSinceRead(uint8_t time);

        void SetTimeoutSinceReadFirstChar(uint8_t time);

        void SetInputBaudRate(unsigned int baudrate);

        void SetOutputBaudRate(unsigned int baudrate);

        void SetHandOnLastCall(bool enable);

        void SetImplementationInputProcessing(bool enable);
        
    private:
        int m_serial_fd;
    };
};

#endif // BEECOLL_SERIAL_NODE_HH