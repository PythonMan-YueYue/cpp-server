#ifndef DTCPSERVER_H
#define DTCPSERVER_H

#include "DSockAPI.h"

class DTcpServer : public DSockAPI
{
public:
    DTcpServer();

    /**
     * @brief init
     * @param port
     * @return
     */
    bool init(const int &port);

    /**
     * @brief acceptClient
     * @return
     */
    bool acceptClient();

    /**
     * @brief readMsg
     * @param buf
     * @param length
     * @param s
     * @param us
     * @return
     */
    bool readMsg(char *buf, int s = 0, int us = 0);

    /**
     * @brief readMsg
     * @param str
     * @param s
     * @param us
     * @return
     */
    bool readMsg(std::string &str, int s = 0, int us = 0);

    /**
     * @brief writeMsg
     * @param buf
     * @param length
     * @return
     */
    bool writeMsg(char *buf, int length = 0);

    /**
     * @brief writeMsg
     * @param str
     * @return
     */
    bool writeMsg(const std::string &str);

private:
    int                     m_ServerFD;            //<! server fd
    int                     m_ClientFD;            //<! client fd
    struct sockaddr_in      m_ServerAddr;          //<! server address
    struct sockaddr_in      m_ClientAddr;          //<! client address
};

#endif // DTCPSERVER_H
