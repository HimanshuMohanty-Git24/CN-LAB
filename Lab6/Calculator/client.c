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
    int sockfd, i;
    char buf[100];
    struct sockaddr_in sa, ca;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6025);

    int num1, num2;
    char operand;

    printf("Enter two numbers and an operand (e.g., 10 + 5): ");
    scanf("%d %c %d", &num1, &operand, &num2);

    sprintf(buf, "%d %c %d", num1, operand, num2);
    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&sa, sizeof(sa));

    char buf1[100];
    ssize_t length = recvfrom(sockfd, buf1, sizeof(buf1), 0, (struct sockaddr *)&ca, &(socklen_t){sizeof(ca)});
    if (length < 0)
    {
        perror("recvfrom");
        exit(1);
    }
    buf1[length] = '\0';
    printf("Result: %s\n", buf1);

    close(sockfd);

    return 0;
}
