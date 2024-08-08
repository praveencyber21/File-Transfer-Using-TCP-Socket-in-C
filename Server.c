//  File transfer using tcp - Server program
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{

    int sockfd;
    struct sockaddr_in server_socket;
    socklen_t addrlen = sizeof(server_socket);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket Error");
    }
    else
    {
        printf("Socket Created\n");
    }

    server_socket.sin_family = AF_INET;
    server_socket.sin_port = htons(9999);
    server_socket.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_socket, addrlen) < 0)
    {
        perror("Bind error");
    }

    if (listen(sockfd, 3) < 0)
    {
        perror("Listen error");
    }

    printf("Server is listening...\n");

    int new_sockfd;
    new_sockfd = accept(sockfd, (struct sockaddr *)&server_socket, &addrlen);

    char buffer[50] = "Message from server";
    send(new_sockfd, buffer, sizeof(buffer), 0);

    close(sockfd);
    close(new_sockfd);

    return 0;
}