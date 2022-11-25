#include "SerialInterface.hh"

// STD headers
#include <vector>

// LINUX headers
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/file.h>

// TODO: DEBUG headers
#include <iostream>

using namespace BeeCoLL;

SerialInterface::SerialInterface(const std::string &serial_device)
{
    m_serial_fd = open(serial_device.c_str(), O_RDWR);
    if (m_serial_fd < 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }

    // ClearSerial();
}

SerialInterface::~SerialInterface()
{
    if (m_serial_fd >= 0)
    {
        if (close(m_serial_fd) != 0)
        {
            // TODO: throw something
            std::cout << std::strerror(errno) << std::endl;
        }
    }
}

int
SerialInterface::GetSerialFD() const
{
    return m_serial_fd;
}

void SerialInterface::WriteToSerial(const std::vector<uint8_t>& data)
{
    unsigned int bytes = write(m_serial_fd, data.data(), data.size());
    if (bytes != data.size())
    {
        // TODO: throw something
        std::cout << "send mismatch " << std::strerror(errno) << std::endl;
    }
}

std::vector<uint8_t>
SerialInterface::ReadFromSerial(std::size_t read_n_bytes)
{
    std::vector<uint8_t> data;
    data.resize(read_n_bytes);
    ssize_t bytes = 0;
    ssize_t size_tmp = read_n_bytes;
    do
    {
        ssize_t result = read(m_serial_fd, data.data() + bytes, size_tmp);
        if (result == 0)
        {
            break;
        }
        bytes += result;
        size_tmp = read_n_bytes - bytes;
    } while (bytes != read_n_bytes);

    
    // ssize_t bytes = read(m_serial_fd, data.data(), read_n_bytes);
    // if (bytes != read_n_bytes)
    // {
    //     std::cout << "read serial mismatch" << std::endl;
    // }
    return data;
}

void
SerialInterface::LockFD(int fd)
{
    if(flock(fd, LOCK_EX | LOCK_NB) == -1)
    {
        std::cout << "Unable to lock fd" << std::endl;
        // TODO: throw something
    }
}

void SerialInterface::ClearSerial()
{
    if (fcntl(m_serial_fd, F_SETFL, fcntl(m_serial_fd, F_GETFL) | O_NONBLOCK) < 0) {
        // TODO: throw something
        std::cout << "clear failed" << std::endl;
    }

    uint8_t bytes = 0;
    do
    {
        std::vector<uint8_t> bytes = ReadFromSerial(255);
    } while (bytes == 255);

    if (fcntl(m_serial_fd, F_SETFL, fcntl(m_serial_fd, F_GETFL) & ~O_NONBLOCK) < 0) {
        // TODO: throw something
        std::cout << "clear failed" << std::endl;
    }
}

void
SerialInterface::SetParityBit(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_cflag |= PARENB;
    }
    else
    {
        tty_attr.c_cflag &= ~PARENB;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetStopBits(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_cflag |= CSTOPB;
    }
    else
    {
        tty_attr.c_cflag &= ~CSTOPB;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetBitsInByte(uint8_t bits)
{
    if (bits < 5 || bits > 8)
    {
        // TODO: throw something
        // not valid
        return;
    }
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    tty_attr.c_cflag &= ~CSIZE;
    if (bits == 5)
    {
        tty_attr.c_cflag |= CS5;
    }
    else if (bits == 6)
    {
        tty_attr.c_cflag |= CS6;
    }
    else if (bits == 7)
    {
        tty_attr.c_cflag |= CS7;
    }
    else if (bits == 8)
    {
        tty_attr.c_cflag |= CS8;
    }

    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetControlFlow(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_cflag |= CRTSCTS;
    }
    else
    {
        tty_attr.c_cflag &= ~CRTSCTS;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetModemLine(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= CREAD;
        tty_attr.c_lflag |= CLOCAL;
    }
    else
    {
        tty_attr.c_lflag &= ~CREAD;
        tty_attr.c_lflag &= ~CLOCAL;
    }
    tty_attr.c_cflag |= CREAD | CLOCAL;
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetCanonicalMode(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= ICANON;
    }
    else
    {
        tty_attr.c_lflag &= ~ICANON;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetEcho(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= ECHO;
        tty_attr.c_lflag |= ECHOE;
        tty_attr.c_lflag |= ECHONL;
    }
    else
    {
        tty_attr.c_lflag &= ~ECHO;
        tty_attr.c_lflag &= ~ECHOE;
        tty_attr.c_lflag &= ~ECHONL;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetSignalChars(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= ISIG;
    }
    else
    {
        tty_attr.c_lflag &= ~ISIG;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetSoftwareFlowControl(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= IXON;
        tty_attr.c_lflag |= IXOFF;
        tty_attr.c_lflag |= IXANY;
    }
    else
    {
        tty_attr.c_lflag &= ~IXON;
        tty_attr.c_lflag &= ~IXOFF;
        tty_attr.c_lflag &= ~IXANY;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetOutputSpecialChars(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= IGNBRK;
        tty_attr.c_lflag |= BRKINT;
        tty_attr.c_lflag |= PARMRK;
        tty_attr.c_lflag |= ISTRIP;
        tty_attr.c_lflag |= INLCR;
        tty_attr.c_lflag |= IGNCR;
        tty_attr.c_lflag |= ICRNL;
    }
    else
    {
        tty_attr.c_lflag &= ~IGNBRK;
        tty_attr.c_lflag &= ~BRKINT;
        tty_attr.c_lflag &= ~PARMRK;
        tty_attr.c_lflag &= ~ISTRIP;
        tty_attr.c_lflag &= ~INLCR;
        tty_attr.c_lflag &= ~IGNCR;
        tty_attr.c_lflag &= ~ICRNL;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetInputSpecialChars(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= OPOST;
        tty_attr.c_lflag |= ONLCR;
    }
    else
    {
        tty_attr.c_lflag &= ~OPOST;
        tty_attr.c_lflag &= ~ONLCR;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetTimeoutSinceRead(uint8_t time)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    tty_attr.c_cc[VMIN] = 0;
    tty_attr.c_cc[VTIME] = time;

    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetTimeoutSinceReadFirstChar(uint8_t time)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    tty_attr.c_cc[VMIN] = 1;
    tty_attr.c_cc[VTIME] = time;

    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetInputBaudRate(unsigned int baudrate)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    cfsetispeed(&tty_attr, baudrate);
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetOutputBaudRate(unsigned int baudrate)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    cfsetospeed(&tty_attr, baudrate);
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
SerialInterface::SetHandOnLastCall(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= HUPCL;
    }
    else
    {
        tty_attr.c_lflag &= ~HUPCL;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}
