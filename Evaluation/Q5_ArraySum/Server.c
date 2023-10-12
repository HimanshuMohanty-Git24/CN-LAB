#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd, length, i, sum = 0;
    int arr[100]; // Array to store received elements
    struct sockaddr_in sa, ca;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6025);

    i = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("Bind Status: %d\n", i);

    length = sizeof(ca);
    // Receive the size of the array
    recvfrom(sockfd, &length, sizeof(length), 0, (struct sockaddr *)&ca, &length);

    // Receive the array elements
    recvfrom(sockfd, arr, length * sizeof(int), 0, (struct sockaddr *)&ca, &length);

    // Calculate the sum of array elements
    int size = length;
    for (i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    printf("Received Array Elements and Calculated Sum.\nSending Sum Back to Client...\n");

    // Sending sum back to client
    sendto(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&ca, sizeof(ca));

    close(sockfd);
    return 0;
}
