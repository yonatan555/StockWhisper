#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>
#define SOCKET_PATH "/home/yonatan/project/tockwhisper.sock"
class SocketServer
{
public:
    SocketServer(const std::string &socket_path);
    ~SocketServer();

    bool start();
    void stop();

private:
    std::string socket_path_;
    int server_fd_;
    int client_fd_;

    bool bindSocket();
    bool listenSocket();
    bool acceptConnection();
    void handleClient();
};

#endif // SOCKETSERVER_H