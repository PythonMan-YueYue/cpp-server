#include "DSockAPI.h"

DSockAPI::DSockAPI()
    : m_TimeOut(false)
{

}
bool DSockAPI::dsend(const int &fd, const char *buf, const size_t &size)
{
    if (fd < 0) {
        return false;
    }

    int leftBufSize = static_cast<int>(size); // The number of bytes left in the unsent message
    int curPos = 0; // current pos
    while (leftBufSize > 0) {
        int sendSize = static_cast<int>(send(fd, buf + curPos, static_cast<size_t>(leftBufSize), 0));
        if (sendSize < 0) {
            return false;
        }
        leftBufSize -= sendSize;
        curPos += sendSize;
    }
    return true;
}

bool DSockAPI::dsend(const int &fd, const std::string &msg)
{
    if (fd < 0) {
        return false;
    }

    size_t size = sizeof(msg);
    const char *buf = msg.c_str();
    return dsend(fd, buf, size);
}

bool DSockAPI::drecv(const int &fd, char *buf, const size_t &size)
{
    if (fd < 0) {
        return false;
    }

    int leftBufSize = static_cast<int>(size); //How many messages have not been received
    int curPos = 0; // The length of the currently received buf

    while (leftBufSize > 0) {
        int readSize = static_cast<int>(recv(fd, buf + curPos, static_cast<size_t>(leftBufSize), 0));
        if (readSize < 0) {
            return false;
        }
        leftBufSize -= readSize;
        curPos += readSize;
    }
    return true;
}

bool DSockAPI::drecv(const int &fd, std::string &msg)
{
    if (fd < 0) {
        return false;
    }

    char buf[1024];
    int readSize = static_cast<int>(recv(fd, buf, static_cast<size_t>(sizeof(buf)), 0));
    while (readSize > 0) {
        msg.append(buf);
        memset(buf, 0, sizeof(buf));
    }
    if (readSize < 0) {
        return false;
    }
    return true;
}

bool DSockAPI::waiting(const int &fd, const int &sec, const int &usec)
{
    if (fd < 0) {
        return false;
    }

    if (sec <= 0 && usec <= 0) {
        return true;
    }

    fd_set set;
    FD_ZERO(&set);
    FD_SET(fd, &set);

    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = sec;

    int res = select(fd + 1, &set, 0, 0, &timeout);
    if (res <= 0) {
        // =0 -> timeout
        // <0 -> error
        // >0 -> right
        if (res == 0) {
            m_TimeOut = true;
        } else {
            m_TimeOut = false;
        }
        return false;
    }
    return true;
}

bool DSockAPI::timeout()
{
    return m_TimeOut;
}

void DSockAPI::closeFD(int &fd)
{
    close(fd);
    fd = -1;
}

char *DSockAPI::ipFromAddr(const struct in_addr &sin_addr)
{
    return inet_ntoa(sin_addr);
}
