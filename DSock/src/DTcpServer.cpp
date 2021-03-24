#include "DTcpServer.h"

DTcpServer::DTcpServer()
    : m_ServerFD(-1)
    , m_ClientFD(-1)
{

}

bool DTcpServer::init(const int &port)
{
    if (m_ServerFD > 0) {
        close(m_ServerFD);
        m_ServerFD = -1;
    }

    m_ServerFD = socket(AF_INET, SOCK_STREAM, 0);
    if (m_ServerFD < 0) {
        return false;
    }

    /**
     *  SO_REUSEADDR makes a port ready to be used again immediately after it is released.
     *  In general, a port will wait two minutes before being used again
     */
    int option = 1;
    setsockopt(m_ServerFD, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    /**
     *  Initialize the server address
     */
    memset(&m_ServerAddr, 0, sizeof(m_ServerAddr));
    m_ServerAddr.sin_port = htons(static_cast<unsigned short>(port));
    m_ServerAddr.sin_family = AF_INET;
    m_ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /**
     *  Bind to the service address
     */
    bool res = bind(m_ServerFD, reinterpret_cast<struct sockaddr *>(&m_ServerAddr), sizeof(m_ServerAddr));
    if (res != 0) {
        closeFD(m_ServerFD);
        return false;
    }

    /**
     *  listen
     */
    res = listen(m_ServerFD, 5);
    if (res != 0) {
        closeFD(m_ServerFD);
        return false;
    }

    return true;
}

bool DTcpServer::acceptClient()
{
    if (m_ServerFD < 0) {
        return false;
    }

    /**
     *  Accept the connection request from the client
     */
    memset(&m_ClientAddr, 0, sizeof(m_ClientAddr));
    unsigned long size = sizeof(struct sockaddr_in);
    m_ClientFD = accept(m_ServerFD, reinterpret_cast<struct sockaddr *>(&m_ClientAddr), reinterpret_cast<socklen_t *>(&size));
    if (m_ClientFD < 0) {
        return false;
    }
    return true;
}

bool DTcpServer::readMsg(char *buf, int s, int us)
{
    /**
     * Wait for a certain amount of time and return if the time expires
     */
    bool res = waiting(m_ClientFD, s, us);
    if (!res) {
        return false;
    }

    /**
     * Gets the length of the buf to be read
     */
    int bufLen = 0;
    res = drecv(m_ClientFD, reinterpret_cast<char *>(&bufLen), 4);
    bufLen = static_cast<int>(ntohl(static_cast<unsigned int>(bufLen)));

    /**
     * read buf
     */
    res = drecv(m_ClientFD, buf, static_cast<size_t>(bufLen));
    if (!res) {
        return false;
    }

    return true;
}

bool DTcpServer::readMsg(std::string &str, int s, int us)
{
    return true;
}

bool DTcpServer::writeMsg(char *buf, int length)
{
    return true;
}

bool DTcpServer::writeMsg(const std::string &str)
{
    return true;
}
