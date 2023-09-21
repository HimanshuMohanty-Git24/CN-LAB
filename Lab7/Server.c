#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int sockfd, fd[4], length, i;
    char buf[100], buf1[100];
    struct sockaddr_in sa, ca[4];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6034);

    i = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("test %d %d\n", sockfd, i);

    listen(sockfd, 5);

    for (int clientCount = 0; clientCount < 4; clientCount++)
    {
        length = sizeof(ca[clientCount]);
        fd[clientCount] = accept(sockfd, (struct sockaddr *)&ca[clientCount], &length);

        if (fd[clientCount] < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
    }

    for (int clientCount = 0; clientCount < 4; clientCount++)
    {
        int k = recv(fd[clientCount], buf, 100, 0);
        buf[k] = '\0';
        printf("Client %d: %s \n", clientCount + 1, buf);

        printf("Enter a message for Client %d:\t", clientCount + 1);
        fgets(buf1, sizeof(buf1), stdin);
        send(fd[clientCount], buf1, strlen(buf1), 0);
    }

    for (int clientCount = 0; clientCount < 4; clientCount++)
    {
        close(fd[clientCount]);
    }

    close(sockfd);

    return 0;
}
