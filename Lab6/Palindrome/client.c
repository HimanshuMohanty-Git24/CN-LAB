// Wap to send a string from client side and check if it's a palindrome in server side
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

    printf("Enter a String\t");
    fgets(buf, sizeof(buf), stdin);
    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&sa, sizeof(sa));

    // recieve result from server
    length = sizeof(ca);
    recvfrom(sockfd, buf1, 100, 0, (struct sockaddr *)&ca, &length);
    if (buf1 == "ispalindrome")
    {
        printf("it's a Palindrome\n");
    }
    else
    {
        printf("it's not a  Palindrome\n");
    }
    close(sockfd);

    return 0;
}