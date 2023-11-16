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
    struct sockaddr_in sa, ca;
    struct UserDetails users[5];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(6025);

    bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));

    printf("Server is waiting...\n");

    // Receive details from clients for user registration
    for (i = 0; i < 5; i++)
    {
        length = sizeof(ca);
        recvfrom(sockfd, &users[i], sizeof(struct UserDetails), 0, (struct sockaddr *)&ca, &length);
        printf("Received registration details for User %d\n", i + 1);
    }

    while (1)
    {
        // Receive login details from clients
        struct UserDetails loginUser;
        length = sizeof(ca);
        recvfrom(sockfd, &loginUser, sizeof(struct UserDetails), 0, (struct sockaddr *)&ca, &length);

        // Check if login details match any registered user
        int userIndex = -1;
        for (i = 0; i < 5; i++)
        {
            if (strcmp(users[i].userId, loginUser.userId) == 0 && strcmp(users[i].password, loginUser.password) == 0)
            {
                userIndex = i;
                break;
            }
        }

        // Send login status to client
        if (userIndex != -1)
        {
            sendto(sockfd, "Log In Successful. You can now transfer.", strlen("Log In Successful. You can now transfer."), 0, (struct sockaddr *)&ca, sizeof(ca));
        }
        else
        {
            sendto(sockfd, "Log In Unsuccessful.", strlen("Log In Unsuccessful."), 0, (struct sockaddr *)&ca, sizeof(ca));
        }
    }

    close(sockfd);

    return 0;
}
