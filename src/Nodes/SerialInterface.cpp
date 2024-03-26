#include "SerialInterface.hh"

// STD headers
#include <vector>
#include <cstdint>

// LINUX headers
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/file.h>

// TODO: DEBUG headers
#include <iostream>

BeeCoLL::SerialInterface::SerialInterface(const std::string &serial_device)
{
    m_serial_fd = open(serial_device.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (m_serial_fd < 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }

    // ClearSerial();
}

BeeCoLL::SerialInterface::SerialInterface(int serial_fd) :
    m_serial_fd(serial_fd)
{

}

BeeCoLL::SerialInterface::~SerialInterface()
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
BeeCoLL::SerialInterface::GetSerialFD() const
{
    return m_serial_fd;
}

void
BeeCoLL::SerialInterface::WriteToSerial(const std::vector<uint8_t>& data)
{
    unsigned int bytes = write(m_serial_fd, data.data(), data.size());
    if (bytes != data.size())
    {
        // TODO: throw something
        std::cout << "send mismatch " << std::strerror(errno) << std::endl;
    }
}

std::vector<uint8_t>
BeeCoLL::SerialInterface::ReadFromSerial(std::size_t read_n_bytes)
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
BeeCoLL::SerialInterface::LockFD(int fd)
{
    if(flock(fd, LOCK_EX | LOCK_NB) == -1)
    {
        std::cout << "Unable to lock fd" << std::endl;
        // TODO: throw something
    }
}

void
BeeCoLL::SerialInterface::ClearSerial()
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
BeeCoLL::SerialInterface::SetParityBit(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    tty_attr.c_cflag = INPCK;
    tty_attr.c_cflag = ISTRIP;
    if (enable == true)
    {
        tty_attr.c_cflag |= PARENB;
        tty_attr.c_cflag |= PARODD;
    }
    else
    {
        tty_attr.c_cflag &= ~PARENB;
        tty_attr.c_cflag &= ~PARODD;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
BeeCoLL::SerialInterface::SetStopBits(bool enable)
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
BeeCoLL::SerialInterface::SetBitsInByte(uint8_t bits)
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
BeeCoLL::SerialInterface::SetControlFlow(bool enable)
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
BeeCoLL::SerialInterface::SetModemLine(bool enable)
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
BeeCoLL::SerialInterface::SetCanonicalMode(bool enable)
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
BeeCoLL::SerialInterface::SetEcho(bool enable)
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
        tty_attr.c_lflag |= ECHOK;
        tty_attr.c_lflag |= ECHONL;
    }
    else
    {
        tty_attr.c_lflag &= ~ECHO;
        tty_attr.c_lflag &= ~ECHOE;
        tty_attr.c_lflag &= ~ECHOK;
        tty_attr.c_lflag &= ~ECHONL;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
BeeCoLL::SerialInterface::SetSignalChars(bool enable)
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
BeeCoLL::SerialInterface::SetSoftwareFlowControl(bool enable)
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
#ifdef IXANY
        tty_attr.c_lflag |= IXANY;
#endif
    }
    else
    {
        tty_attr.c_lflag &= ~IXON;
        tty_attr.c_lflag &= ~IXOFF;
#ifdef IXANY
        tty_attr.c_lflag &= ~IXANY;
#endif
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}

void
BeeCoLL::SerialInterface::SetOutputSpecialChars(bool enable)
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
BeeCoLL::SerialInterface::SetInputSpecialChars(bool enable)
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
BeeCoLL::SerialInterface::SetTimeoutSinceRead(uint8_t time)
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
BeeCoLL::SerialInterface::SetTimeoutSinceReadFirstChar(uint8_t time)
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
BeeCoLL::SerialInterface::SetInputBaudRate(unsigned int baudrate)
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
BeeCoLL::SerialInterface::SetOutputBaudRate(unsigned int baudrate)
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
BeeCoLL::SerialInterface::SetHandOnLastCall(bool enable)
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

void
BeeCoLL::SerialInterface::SetImplementationInputProcessing(bool enable)
{
    struct termios tty_attr;
    if (tcgetattr(m_serial_fd, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
    if (enable == true)
    {
        tty_attr.c_lflag |= IEXTEN;
    }
    else
    {
        tty_attr.c_lflag &= ~IEXTEN;
    }
    if (tcsetattr(m_serial_fd, TCSANOW, &tty_attr) != 0)
    {
        // TODO: throw something
        std::cout << std::strerror(errno) << std::endl;
    }
}
