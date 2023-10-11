#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int sockfd, clientfd[5], lenget, i;
    char buffer[100];
    struct sockaddr_in sa, ta1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(60018); // Use htons to convert port to network byte order

    bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("Socket created and bound.\n");

    listen(sockfd, 5);
    lenget = sizeof(ta1);

    fd_set allfd, readfd;
    FD_ZERO(&allfd);
    FD_SET(sockfd, &allfd);
    int maxfd = sockfd + 1;
    i = 0;

    while (1)
    {
        readfd = allfd;
        struct timeval timeout;
        timeout.tv_sec = 30;
        timeout.tv_usec = 50;

        int k = select(maxfd, &readfd, NULL, NULL, &timeout);

        if (FD_ISSET(sockfd, &readfd))
        {
            clientfd[i] = accept(sockfd, (struct sockaddr *)&ta1, &lenget);
            FD_SET(clientfd[i], &allfd);
            if (clientfd[i] >= maxfd)
            {
                maxfd = clientfd[i] + 1;
            }
            i++;
        }

        for (int j = 0; j < i; j++)
        {
            if (FD_ISSET(clientfd[j], &readfd))
            {
                int n = recv(clientfd[j], buffer, sizeof(buffer), 0);
                if (n <= 0)
                {
                    // Client closed the connection or an error occurred
                    close(clientfd[j]);
                    FD_CLR(clientfd[j], &allfd);
                }
                else
                {
                    buffer[n] = '\0';
                    printf("Received: %s\n", buffer);
                    send(clientfd[j], buffer, strlen(buffer), 0);
                }
            }
        }
    }

    close(sockfd);

    return 0;
}