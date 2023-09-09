// Wap to recieve a string from client side a nd cleck if it's a palindrome
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
    recvfrom(sockfd, buf1, 100, 0, (struct sockaddr *)&ca, &length);
    printf("Received %s\n", buf1);

    int len = strlen(buf1);
    for (i = 0; i < len; i++)
    {
        buf[i] = buf1[len - i - 1];
    }
    buf[i] = '\0';
    printf("%s  %s\n", buf, buf1);
    printf("\nSending Result Back to client...\n");
    if (strcmp(buf, buf1) == 0)
    {
        printf("Palindrome\n");
        sendto(sockfd, "ispalindrome", 12, 0, (struct sockaddr *)&ca, sizeof(ca));
    }
    else
    {
        printf("Not Palindrome\n");
        sendto(sockfd, "notpalindrome", 12, 0, (struct sockaddr *)&ca, sizeof(ca));
    }
    close(sockfd);
    return 0;
}
