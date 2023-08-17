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
    struct sockaddr_in sa;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6034);

    i = connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("Connected: %d\n", i);

    printf("Enter a message\t");
    fgets(buf1, sizeof(buf1), stdin);

    send(sockfd, buf1, strlen(buf1), 0);

    int k = recv(sockfd, buf, 100, 0);
    buf[k] = '\0';
    printf("Received: %s\n", buf);

    close(sockfd);

    return 0;
}
