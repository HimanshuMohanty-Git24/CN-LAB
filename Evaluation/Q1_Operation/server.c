#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int isPrime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int sockfd, choice, num, result, i;
    struct sockaddr_in sa, ca;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6025);

    i = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("test %d %d\n", sockfd, i);
    printf("Server is waiting for client...\n");

    int length = sizeof(ca);
    recvfrom(sockfd, &choice, sizeof(choice), 0, (struct sockaddr *)&ca, &length);
    recvfrom(sockfd, &num, sizeof(num), 0, (struct sockaddr *)&ca, &length);

    switch (choice)
    {
    case 1: // Prime or Not Prime
        result = isPrime(num);
        break;
    case 2: // Even or Odd
        result = (num % 2 == 0) ? 1 : 0;
        break;
    case 3: // Positive or Negative
        result = (num >= 0) ? 1 : 0;
        break;
    default:
        printf("Invalid choice.\n");
        close(sockfd);
        return 1;
    }

    // Sending the result back to the client
    printf("Operation Complete...\n");
    printf("Sending Result to Client :)...\n");
    sendto(sockfd, &result, sizeof(result), 0, (struct sockaddr *)&ca, sizeof(ca));

    close(sockfd);
    return 0;
}
