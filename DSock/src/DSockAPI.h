#ifndef DSOCKAPI_H
#define DSOCKAPI_H

#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include <netdb.h>

/**
 * @brief The DSockAPI class
 */
class DSockAPI
{
public:
    DSockAPI();

protected:
    /**
     * @brief sendMsg
     * @param fd
     * @param buf
     * @param size
     * @return
     */
    bool dsend(const int &fd, const char *buf, const size_t &size);

    /**
     * @brief sendMsg
     * @param fd
     * @param msg
     * @return
     */
    bool dsend(const int &fd, const std::string &msg);

    /**
     * @brief recvMsg
     * @param fd
     * @param buf
     * @param size
     * @return
     */
    bool drecv(const int &fd, char *buf, const size_t &size);

    /**
     * @brief recvMsg
     * @param fd
     * @param msg
     * @return
     */
    bool drecv(const int &fd, std::string &msg);

    /**
     * @brief waiting
     * @param fd
     * @param sec
     * @param usec
     * @return
     */
    bool waiting(const int &fd, const int &sec = 0, const int &usec = 0);

    /**
     * @brief timeout
     * @return
     */
    bool timeout();

    /**
     * @brief closeFD
     * @param fd
     */
    void closeFD(int &fd);

    /**
     * @brief ip
     * @param sin_addr
     * @return
     */
    char *ipFromAddr(const struct in_addr &sin_addr);

private:
    bool                m_TimeOut;              //<! timeout
};

#endif // DSOCKAPI_H
