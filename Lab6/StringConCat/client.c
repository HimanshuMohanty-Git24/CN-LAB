// Wap to send 2 string from client to server and server will concatenate them and send back to client.
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
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

    // Client side:

    // Send the first string
    printf("Enter the first string: ");
    fgets(buf, sizeof(buf), stdin);
    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&sa, sizeof(sa));

    // Send the second string
    printf("Enter the second string: ");
    fgets(buf1, sizeof(buf1), stdin);
    sendto(sockfd, buf1, strlen(buf1), 0, (struct sockaddr *)&sa, sizeof(sa));

    // Receive the concatenated string
    length = sizeof(ca);
    int k = recvfrom(sockfd, buf, 100, 0, (struct sockaddr *)&ca, &length);
    buf[k] = '\0';
    printf("Receaved: %s \n", buf);

    close(sockfd);

    return 0;
}