#include "DTcpServer.h"
#include <QDebug>

DTcpServer::DTcpServer()
{
    m_listenfd = -1;
    m_connfd = -1;
    m_socklen = 0;
    m_btimeout = false;
}

bool DTcpServer::InitServer(const unsigned int port)
{
    if (m_listenfd > 0) { close(m_listenfd); m_listenfd = -1; }

    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // Linux如下
    int opt = 1; unsigned int len = sizeof(opt);
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, len);

    memset(&m_servaddr, 0, sizeof(m_servaddr));
    m_servaddr.sin_family = AF_INET;
    m_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_servaddr.sin_port = htons(port);
    if (bind(m_listenfd, (struct sockaddr *)&m_servaddr, sizeof(m_servaddr)) != 0) {
        CloseListen(); return false;
    }

    if (listen(m_listenfd, 5) != 0) {
        CloseListen(); return false;
    }

    m_socklen = sizeof(struct sockaddr_in);

    return true;
}

bool DTcpServer::Accept()
{
    if (m_listenfd == -1) {
        qInfo() << " ************************ Accept 001";
        return false;
    }

    if ((m_connfd = accept(m_listenfd, (struct sockaddr *)&m_clientaddr, (socklen_t *)&m_socklen)) < 0) {
        qInfo() << " ************************ Accept 002";
        return false;
    }

    return true;
}

char *DTcpServer::GetIP()
{
    return (inet_ntoa(m_clientaddr.sin_addr));
}

bool DTcpServer::Read(char *buffer, const int itimeout)
{
    if (m_connfd == -1) return false;

    if (itimeout > 0) {
        fd_set tmpfd;

        FD_ZERO(&tmpfd);
        FD_SET(m_connfd, &tmpfd);

        struct timeval timeout;
        timeout.tv_sec = itimeout; timeout.tv_usec = 0;

        m_btimeout = false;

        int i;
        if ((i = select(m_connfd + 1, &tmpfd, 0, 0, &timeout)) <= 0) {
            if (i == 0) m_btimeout = true;
            return false;
        }
    }

    m_buflen = 0;
    return (TcpRead(m_connfd, buffer, &m_buflen));
}

bool DTcpServer::Write(const char *buffer, const int ibuflen)
{
    if (m_connfd == -1) return false;

    fd_set tmpfd;

    FD_ZERO(&tmpfd);
    FD_SET(m_connfd, &tmpfd);

    struct timeval timeout;
    timeout.tv_sec = 5; timeout.tv_usec = 0;

    m_btimeout = false;

    int i;
    if ((i = select(m_connfd + 1, 0, &tmpfd, 0, &timeout)) <= 0) {
        if (i == 0) m_btimeout = true;
        return false;
    }

    int ilen = ibuflen;
    if (ilen == 0) ilen = strlen(buffer);

    return (TcpWrite(m_connfd, buffer, ilen));
}

void DTcpServer::CloseListen()
{
    if (m_listenfd > 0) {
        close(m_listenfd); m_listenfd = -1;
    }
}

void DTcpServer::CloseClient()
{
    if (m_connfd > 0) {
        close(m_connfd); m_connfd = -1;
    }
}

DTcpServer::~DTcpServer()
{
    CloseListen(); CloseClient();
}

bool DTcpServer::TcpWrite(const int sockfd, const char *buffer, const int ibuflen)
{
    if (sockfd == -1) return false;

    fd_set tmpfd;

    FD_ZERO(&tmpfd);
    FD_SET(sockfd, &tmpfd);

    struct timeval timeout;
    timeout.tv_sec = 5; timeout.tv_usec = 0;

    if (select(sockfd + 1, 0, &tmpfd, 0, &timeout) <= 0) return false;

    int ilen = 0;

    // 如果长度为0，就采用字符串的长度
    if (ibuflen == 0) ilen = strlen(buffer);
    else ilen = ibuflen;

    int ilenn = htonl(ilen); // 转换为网络字节序。

    char strTBuffer[ilen + 4];
    memset(strTBuffer, 0, sizeof(strTBuffer));
    memcpy(strTBuffer, &ilenn, 4);
    memcpy(strTBuffer + 4, buffer, ilen);

    if (Writen(sockfd, strTBuffer, ilen + 4) == false) return false;

    return true;
}

bool DTcpServer::Writen(const int sockfd, const char *buffer, const size_t n)
{
    int nLeft, idx, nwritten;
    nLeft = n;
    idx = 0;
    while (nLeft > 0) {
        if ((nwritten = send(sockfd, buffer + idx, nLeft, 0)) <= 0) return false;

        nLeft -= nwritten;
        idx += nwritten;
    }

    return true;
}

bool DTcpServer::Readn(const int sockfd, char *buffer, const size_t n)
{
    int nLeft, nread, idx;

    nLeft = n;
    idx = 0;

    while (nLeft > 0) {
        if ((nread = recv(sockfd, buffer + idx, nLeft, 0)) <= 0) return false;

        idx += nread;
        nLeft -= nread;
    }

    return true;
}

bool DTcpServer::TcpRead(const int sockfd, char *buffer, int *ibuflen, const int itimeout)
{
    if (sockfd == -1) return false;

    if (itimeout > 0) {
        fd_set tmpfd;

        FD_ZERO(&tmpfd);
        FD_SET(sockfd, &tmpfd);

        struct timeval timeout;
        timeout.tv_sec = itimeout; timeout.tv_usec = 0;

        int i;
        if ((i = select(sockfd + 1, &tmpfd, 0, 0, &timeout)) <= 0) return false;
    }

    (*ibuflen) = 0;

    if (Readn(sockfd, (char *)ibuflen, 4) == false) return false;

    (*ibuflen) = ntohl(*ibuflen); // 把网络字节序转换为主机字节序。

    if (Readn(sockfd, buffer, (*ibuflen)) == false) return false;

    return true;
}
