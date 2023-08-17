#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int sockfd, fd1, length, i;
    char buf[100], buf1[100];
    struct sockaddr_in sa, ca; // Corrected typo: changed "sa ca" to "sa, ca"

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6034);

    i = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("test %d %d\n", sockfd, i); // Corrected formatting: added space between %d%d

    listen(sockfd, 5);
    length = sizeof(ca); // Corrected: Use 'ca' instead of 'sa' for client address
    fd1 = accept(sockfd, (struct sockaddr *)&ca, &length);

    int k = recv(fd1, buf, 100, 0); // Corrected function name from 'rev' to 'recv'
    buf[k] = '\0';
    printf("%s \n", buf); // Corrected variable name from 'buff' to 'buf'

    printf("Enter a message\t");
    fgets(buf1, sizeof(buf1), stdin); // Changed 'gets' to 'fgets' for safer input reading
    send(fd1, buf1, strlen(buf1), 0);

    close(fd1);
    close(sockfd);

    return 0; // Added return statement
}
