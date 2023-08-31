// UDP SERVER
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

    i = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("test %d %d\n", sockfd, i);

    length = sizeof(ca);
    int k = recvfrom(sockfd, buf, 100, 0, (struct sockaddr *)&ca, &length);
    buf[k] = '\0';
    printf("Receaved: %s \n", buf);
    printf("Enter a message\t");
    fgets(buf1, sizeof(buf1), stdin);
    sendto(sockfd, buf1, strlen(buf1), 0, (struct sockaddr *)&ca, sizeof(ca));
    close(sockfd);
    return 0;
}
