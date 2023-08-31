#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int sockfd, length, i;
    char buf[100], buf1[100];
    struct sockaddr_in sa, ca;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = ("127.0.0.1"); // Listen on any available network interface
    sa.sin_port = htons(6025);

    i = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("test %d %d\n", sockfd, i);
    printf("Ready to receive from client.\n");
    if (i < 0)
    {
        perror("bind failed");
        exit(1);
    }

    length = sizeof(ca);
    int k = recvfrom(sockfd, buf, 100, 0, (struct sockaddr *)&ca, &length);
    buf[k] = '\0';
    printf("Received two numbers from client: %s\n", buf);

    printf("Sum of 2 numbers:\n");
    // Convert string into an array of integers
    int a[2];
    int j = 0;
    char *p = strtok(buf, " ");
    while (p != NULL && j < 2)
    {
        a[j++] = atoi(p);
        p = strtok(NULL, " ");
    }

    if (j == 2)
    {
        int sum = a[0] + a[1];
        printf("Sum: %d\n", sum);

        printf("Sending ACK to client\n");
        sendto(sockfd, "ACK", 3, 0, (struct sockaddr *)&ca, sizeof(ca));
    }
    else
    {
        printf("Invalid data received from client.\n");
    }

    close(sockfd);
    return 0;
}
