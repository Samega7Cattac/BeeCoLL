#include "Serial.hh"

BeeCoLL::Serial::~Serial()
{
    
}

BeeCoLL::Serial::Serial(int serial_fd)
{
    m_serial.SetSerialHandler(serial_fd);
}

BeeCoLL::Serial::Serial(const std::string& serial_device) :
    m_serial(serial_device, 9600, serial::Timeout::simpleTimeout(5000))
{

}

BeeCoLL::Serial::Serial(const std::string& serial_device, unsigned int baud_rate) :
    m_serial(serial_device, baud_rate, serial::Timeout::simpleTimeout(5000))
{

}

BeeCoLL::Serial::Serial(const std::string& serial_device, unsigned int baud_rate, unsigned int timeout) :
    m_serial(serial_device, baud_rate, serial::Timeout::simpleTimeout(timeout))
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
    m_serial.waitReadable();
    m_serial.waitByteTimes(read_n_bytes);
    std::vector<uint8_t> data;
    m_serial.read(data, read_n_bytes);
    return data;
}

int
BeeCoLL::Serial::GetSerialFD() const
{
    return m_serial.GetSerialHandler();
}
