#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#define SOCKET_PATH "/home/yonatan/tockwhisper.sock"

int main()
{
    int server_fd, client_fd;
    struct sockaddr_un address;
    char buffer[1024] = {0};

    // Create a Unix domain socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Clear the address structure and set the socket path
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    // Unlink the previous socket file if it exists
    unlink(SOCKET_PATH);

    // Bind the socket to the file path
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1)
    {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on " << SOCKET_PATH << std::endl;

    // Accept client connections
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1)
    {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read the stock name from the client
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0'; // Null-terminate the stock name
        std::cout << "Received stock name: " << buffer << std::endl;

        // Here you could add code to query a stock API or process the stock name
        // For demonstration, we just send back a confirmation message
        write(client_fd, "Stock name received and processed.", strlen("Stock name received and processed."));
    }
    else
    {
        std::cout << "Failed to read stock name." << std::endl;
    }

    // Clean up
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);

    return 0;
}