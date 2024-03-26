#ifndef BEECOLL_NODES_SERIAL_HH
#define BEECOLL_NODES_SERIAL_HH

#include <vector>
#include <cstdint>
#include <string>
#include <serial/serial.h>

namespace BeeCoLL
{
    class Serial
    {
    public:
        virtual ~Serial();

        Serial(const std::string& serial_device, unsigned int baud_rate);
        Serial(const std::string& serial_device, unsigned int baud_rate, unsigned int timeout);

        void WriteToSerial(const std::vector<uint8_t>& data);
        std::vector<uint8_t> ReadFromSerial(std::size_t read_n_bytes);
    protected:
        explicit Serial(const std::string& serial_device);
        explicit Serial(int serial_fd);

        int GetSerialFD() const;

    
    private:
        serial::Serial m_serial;
    };
};

#endif // BEECOLL_NODES_SERIAL_HH