#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#define MAX_CLIENTS 4
#define BUFFER_SIZE 1024

int main()
{
    int master_socket, new_socket, client_sockets[MAX_CLIENTS], activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    fd_set readfds;

    // Create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8888);

    // Bind the socket to localhost:8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Listener on port %d \n", 8888);

    // Listen for incoming connections
    if (listen(master_socket, 3) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    int addrlen = sizeof(address);
    printf("Waiting for connections ...\n");

    // Initialize client sockets
    for (i = 0; i < MAX_CLIENTS; i++)
    {
        client_sockets[i] = 0;
    }

    while (1)
    {
        FD_ZERO(&readfds);

        // Add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        // Add child sockets to set
        for (i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_sockets[i];

            if (sd > 0)
                FD_SET(sd, &readfds);

            if (sd > max_sd)
                max_sd = sd;
        }

        // Wait for activity on any of the sockets
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (activity < 0)
        {
            perror("Select error");
        }

        // If something happened on the master socket, then it's an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("Accept error");
                exit(EXIT_FAILURE);
            }

            printf("New connection, socket fd is %d, ip is : %s, port : %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Send a welcome message to the client
            char welcome_message[] = "Welcome to the chat server\n";
            send(new_socket, welcome_message, strlen(welcome_message), 0);

            // Add the new socket to the array of sockets
            for (i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        // Check each client socket for messages
        for (i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_sockets[i];

            if (FD_ISSET(sd, &readfds))
            {
                // Check if it was for closing
                if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0)
                {
                    // Somebody disconnected, get his details and print
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    printf("Host disconnected, ip %s, port %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    // Close the socket and mark it as 0 in the list for reuse
                    close(sd);
                    client_sockets[i] = 0;
                }
                else
                {
                    // Process the received message
                    buffer[valread] = '\0'; // Null-terminate the message
                    printf("Client %d: %s\n", i, buffer);

                    // Check for logout message
                    if (strcmp(buffer, "logout") == 0)
                    {
                        printf("Client %d has logged out\n", i);
                        close(sd);
                        client_sockets[i] = 0;
                    }
                    else
                    {
                        // Transform and send the message back to the client
                        // (In this example, just send the same message back)
                        send(sd, buffer, strlen(buffer), 0);
                    }
                }
            }
        }
    }

    return 0;
}
