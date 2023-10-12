#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd, length, i;
    int arr[100]; // Array to store elements
    struct sockaddr_in sa;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6025);

    printf("Enter the number of elements in the array: ");
    int size;
    scanf("%d", &size);

    // Sending the size of the array first
    sendto(sockfd, &size, sizeof(size), 0, (struct sockaddr *)&sa, sizeof(sa));

    printf("Enter the array elements:\n");
    for (i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Sending array to server
    sendto(sockfd, arr, size * sizeof(int), 0, (struct sockaddr *)&sa, sizeof(sa));

    int sum;
    // receive sum from server
    recvfrom(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&sa, &length);

    printf("Sum of Array Elements received from server: %d\n", sum);

    close(sockfd);
    return 0;
}
