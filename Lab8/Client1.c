#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int sockfd;
    char buffer[100];
    struct sockaddr_in sa;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(60018); // Use htons to convert port to network byte order

    connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("Connected to the server.\n");

    while (1)
    {
        printf("Enter a message: ");
        fgets(buffer, sizeof(buffer), stdin);

        send(sockfd, buffer, strlen(buffer), 0);

        int n = recv(sockfd, buffer, sizeof(buffer), 0);
        if (n <= 0)
        {
            printf("Server disconnected.\n");
            break;
        }
        buffer[n] = '\0';
        printf("Server says: %s", buffer);
    }

    close(sockfd);

    return 0;
}