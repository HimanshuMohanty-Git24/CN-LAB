#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd, choice, num, result;
    struct sockaddr_in sa;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6025);

    printf("Enter choice (1: Prime/Not Prime, 2: Even/Odd, 3: Positive/Negative): ");
    scanf("%d", &choice);

    printf("Enter a number: ");
    scanf("%d", &num);

    // Sending choice and number to server
    sendto(sockfd, &choice, sizeof(choice), 0, (struct sockaddr *)&sa, sizeof(sa));
    sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr *)&sa, sizeof(sa));

    // Receiving the result from the server
    int length = sizeof(sa);
    recvfrom(sockfd, &result, sizeof(result), 0, (struct sockaddr *)&sa, &length);

    switch (choice)
    {
    case 1:
        printf(result ? "Result:Prime\n" : "Result:Not Prime\n");
        break;
    case 2:
        printf(result ? "Result:Even\n" : "Result:Odd\n");
        break;
    case 3:
        printf(result ? "Result:Positive\n" : "Result:Negative\n");
        break;
    default:
        printf("Invalid choice.\n");
    }

    close(sockfd);
    return 0;
}
