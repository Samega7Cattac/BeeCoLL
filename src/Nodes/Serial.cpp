#include "Serial.hh"

BeeCoLL::Serial::~Serial()
{
    
}

BeeCoLL::Serial::Serial(int serial_fd)
{
    m_serial.SetSerialHandler(serial_fd);
}

BeeCoLL::Serial::Serial(const std::string& serial_device) :
    m_serial(serial_device, 9600, serial::Timeout::simpleTimeout(1000))
{

}

void
BeeCoLL::Serial::WriteToSerial(const std::vector<uint8_t>& data)
{
    m_serial.write(data);
}

std::vector<uint8_t>
BeeCoLL::Serial::ReadFromSerial(std::size_t read_n_bytes)
{
    std::string str = m_serial.read(read_n_bytes);
    return std::vector<uint8_t>(str.begin(), str.end());
}

int
BeeCoLL::Serial::GetSerialFD() const
{
    return m_serial.GetSerialHandler();
}
