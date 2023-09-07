// Wap to receive 2 numbers and one operand from the client, calculate the result, and send it back to the client.
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
    sa.sin_addr.s_addr = INADDR_ANY;
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
    int k = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&ca, &length);
    buf[k] = '\0';
    printf("Received: %s\n", buf);

    int num1, num2;
    char operand;

    // Parse the input string
    if (sscanf(buf, "%d %c %d", &num1, &operand, &num2) != 3)
    {
        printf("Invalid input format.\n");
        exit(1);
    }

    int result;
    switch (operand)
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2 == 0)
        {
            printf("Division by zero error.\n");
            exit(1);
        }
        result = num1 / num2;
        break;
    default:
        printf("Invalid operand.\n");
        exit(1);
    }
    printf("Result: %d\n", result);

    sprintf(buf1, "%d", result);
    sendto(sockfd, buf1, strlen(buf1), 0, (struct sockaddr *)&ca, sizeof(ca));
    close(sockfd);

    return 0;
}
