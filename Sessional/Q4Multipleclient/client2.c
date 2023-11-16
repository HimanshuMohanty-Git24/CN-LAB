#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main()
{
    int sock = 0;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Receive the welcome message from the server
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("%s", buffer);

    while (1)
    {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send the message to the server
        send(sock, buffer, strlen(buffer), 0);

        // Check for logout condition
        if (strcmp(buffer, "logout") == 0)
        {
            printf("Logging out...\n");
            break;
        }

        // Receive and display the transformed message from the server
        recv(sock, buffer, BUFFER_SIZE, 0);
        printf("Transformed Message: %s\n", buffer);
    }

    // Close the socket
    close(sock);

    return 0;
}
