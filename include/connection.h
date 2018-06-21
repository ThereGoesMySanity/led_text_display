#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SOCK_ADDR "serv_socket"

class Connection {
    public:
        Connection();
        bool connect();
        void close();
        char* getData();
    private:
        int sock, server_fd;
        struct sockaddr_un address;
        char buffer[256];
};
