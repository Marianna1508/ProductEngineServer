#ifndef CSERVER_H
#define CSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class CServer final
{
public:
    explicit CServer(const int& port);
    ~CServer();
    int bind(int fd);

    int getPort() const;
    void setPort(const int& port);

    int socket(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
    int listen(int fd, int numConn);
    int close(int fd);

    struct sockaddr_in serv_addr;
private:
    int mPort;

};

#endif //CSERVER_H