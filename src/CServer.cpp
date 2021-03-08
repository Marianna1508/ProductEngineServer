#include <iostream>
#include "CServer.h"

CServer::CServer(const int& port)
: mPort(port)
{
    // open connection
}

CServer::~CServer()
{
    // close connection
}

int CServer::getPort() const
{
    return mPort;
}

void CServer::setPort(const int& port)
{
    mPort = port;
}

int CServer::bind(int fd)
{
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(mPort);

    return ::bind(fd, (struct sockaddr *)&serv_addr,
           sizeof(serv_addr));

}
int CServer::socket(int domain, int type, int protocol)
{
    return ::socket(domain, type, protocol);
}
int CServer::listen(int fd, int numConn)
{
    return ::listen(fd, numConn);
}
int CServer::close(int fd)
{
    return ::close(fd);
}
