//  File transfer using tcp - Client program
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in client_address;
    socklen_t addrlen = sizeof(client_address);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket error");
    }
    else
    {
        printf("Socket created\n");
    }
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9999);
    client_address.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&client_address, addrlen) < 0)
    {
        perror("Server is not ready");
    }
    else
    {
        printf("Successfully connected with server\n");
    }

    close(sockfd);

    return 0;
}