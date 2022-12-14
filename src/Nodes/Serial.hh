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

    protected:
        explicit Serial(int serial_fd);
        explicit Serial(const std::string& serial_device);

        int GetSerialFD() const;

        void WriteToSerial(const std::vector<uint8_t>& data);
        std::vector<uint8_t> ReadFromSerial(std::size_t read_n_bytes);
    
    private:
        serial::Serial m_serial;
    };
};

#endif // BEECOLL_NODES_SERIAL_HH