#include "SerialInterface.hh"

// STD headers
#include <vector>

// LINUX headers
#include <fcntl.h>
#include <cstring>
#include <termios.h>
#include <unistd.h>

// TODO: DEBUG headers
#include <iostream>

using namespace BeeCoLL;

SerialInterface::SerialInterface(const std::string& serial_device)
{
    m_serial_fd = open(serial_device.c_str(), O_RDWR);
    if (m_serial_fd < 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    struct termios tty;
    if (tcgetattr(m_serial_fd, &tty) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    if (tcsetattr(m_serial_fd, TCSANOW, &tty) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

SerialInterface::~SerialInterface()
{
    if (m_serial_fd > 0)
    {
        if (close(m_serial_fd) != 0)
        {
            // TODO: throw something
            std::cout << std::strerror(errno) << std::endl;
        }
    }
}

void
SerialInterface::WriteToSerial(const std::vector<uint8_t>& data)
{
    unsigned int bytes = write(m_serial_fd, data.data(), data.size());
    if (bytes != data.size())
    {
        // TODO: throw something
        std::cout << "send mismatch " << std::strerror(errno) << std::endl;
    }
}

std::vector<uint8_t>
SerialInterface::ReadFromSerial(const std::size_t& read_n_bytes)
{
    std::vector<uint8_t> data;
    data.resize(read_n_bytes);
    ssize_t bytes = read(m_serial_fd, data.data(), read_n_bytes);
    if (bytes != read_n_bytes)
    {
        // TODO: throw something
        std::cout << "recv mismatch " << std::strerror(errno) << std::endl;
    }
    return data;
}
