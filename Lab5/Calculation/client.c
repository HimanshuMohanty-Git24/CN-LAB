#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int sockfd, length, i;
    char buf[100], buf1[100];
    struct sockaddr_in sa, ca;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6025);

    printf("Enter 2 numbers separated by a space:\n");
    fgets(buf, sizeof(buf), stdin);
    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&sa, sizeof(sa));

    length = sizeof(ca);
    int k = recvfrom(sockfd, buf1, 100, 0, (struct sockaddr *)&ca, &length);
    buf1[k] = '\0';
    if (strcmp(buf1, "ACK") == 0) // Compare strings with strcmp
        printf("ACK received from server\n");
    else
        printf("ACK not received from server\n");

    close(sockfd);

    return 0;
}
