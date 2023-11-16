#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

struct UserDetails
{
    int accountNo;
    char name[50];
    char accountType[20];
    char userId[20];
    char password[20];
};

int main()
{
    int sockfd, length, i;
    struct sockaddr_in sa;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6025);

    // User registration - send details to server
    struct UserDetails users[5];
    for (i = 0; i < 5; i++)
    {
        printf("Enter details for User %d:\n", i + 1);
        printf("Account No: ");
        scanf("%d", &users[i].accountNo);
        printf("Name: ");
        scanf("%s", users[i].name);
        printf("Account Type (saving/current): ");
        scanf("%s", users[i].accountType);
        printf("User ID: ");
        scanf("%s", users[i].userId);
        printf("Password: ");
        scanf("%s", users[i].password);

        sendto(sockfd, &users[i], sizeof(struct UserDetails), 0, (struct sockaddr *)&sa, sizeof(sa));
    }

    // Simulate login attempt
    struct UserDetails loginUser;
    printf("Enter your User ID and Password for login:\n");
    printf("User ID: ");
    scanf("%s", loginUser.userId);
    printf("Password: ");
    scanf("%s", loginUser.password);

    sendto(sockfd, &loginUser, sizeof(struct UserDetails), 0, (struct sockaddr *)&sa, sizeof(sa));

    // Receive login status from server
    char loginStatus[100];
    length = sizeof(sa);
    recvfrom(sockfd, loginStatus, sizeof(loginStatus), 0, (struct sockaddr *)&sa, &length);
    printf("%s\n", loginStatus);

    close(sockfd);

    return 0;
}
