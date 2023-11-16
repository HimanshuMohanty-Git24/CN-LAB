#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

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
    struct UserDetails user;
    printf("Enter your details for registration:\n");
    printf("Account No: ");
    scanf("%d", &user.accountNo);
    printf("Name: ");
    scanf("%s", user.name);
    printf("Account Type (saving/current): ");
    scanf("%s", user.accountType);
    printf("User ID: ");
    scanf("%s", user.userId);
    printf("Password: ");
    scanf("%s", user.password);

    sendto(sockfd, &user, sizeof(struct UserDetails), 0, (struct sockaddr *)&sa, sizeof(sa));

    // User login - send details to server
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
