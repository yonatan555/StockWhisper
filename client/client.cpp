#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#define SOCKET_PATH "/home/yonatan/tockwhisper.sock"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <command>" << std::endl;
        return 1;
    }

    int sock_fd;
    struct sockaddr_un address;
    char buffer[1024];

    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd == -1)
    {
        perror("socket failed");
        return 1;
    }

    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    if (connect(sock_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("connect failed");
        close(sock_fd);
        return 1;
    }

    std::string command = argv[1];
    write(sock_fd, command.c_str(), command.length());

    ssize_t bytes_read = read(sock_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0'; // Null-terminate the response string
        std::cout << "Server response: " << buffer << std::endl;
    }

    close(sock_fd);

    return 0;
}