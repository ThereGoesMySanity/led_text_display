#include "connection.h"
Connection::Connection() {
    memset(&address, 0, sizeof(address));
    char* path = strcpy(address.sun_path, SOCK_ADDR); 
    unlink(path);
    address.sun_family = AF_UNIX;

    if((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0){
        printf("Socket failed\n");
        return;
    }

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0)
    {
        printf("bind failed\n");
        return;
    }
    chown(path, 1001, 33);
    chmod(path, 0770);

    if(listen(server_fd, 3) < 0) {
        printf("listen error\n");
        return;
    }
    printf("init complete\n");
}
bool Connection::connect() {
    printf("wait for connection...\n");
    if((sock = accept(server_fd, NULL, NULL)) < 0) {
        printf("accept error\n");
        return false;
    }
    printf("connection accepted\n");
    buffer[0] = 0;
    return true;
}
void Connection::close() {
    //TODO: Figure out how close() works
}
/*
void Connection::test() {
    int result = read(sock, buffer, 8);
    printf("%s\n", buffer);
    char *msg = "test2";
    send(sock, msg, strlen(msg), 0);
}
*/
char* Connection::getData() {
    int result = read(sock, buffer, 256);
    buffer[result] = 0;
    return result > 0? buffer : nullptr;
}
