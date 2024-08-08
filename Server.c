//  File transfer using tcp - Server program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024
void send_file(int new_sockfd)
{
    FILE *fp = fopen("send.txt", "r");

    // if (fp == NULL)
    // {
    //     perror("File error");
    //     send(new_sockfd, "File error", SIZE, 0);

    //     exit(EXIT_FAILURE);
    // }

    char buffer[SIZE];
    while (1)
    {
        if (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            send(new_sockfd, buffer, strlen(buffer), 0);
        }
        else
        {
            break;
        }
        bzero(buffer, SIZE);
    }

    printf("[\u2714] File sended successfully\n");
    fclose(fp);
}

int main(int argc, char const *argv[])
{

    int sockfd;
    struct sockaddr_in server_socket;
    socklen_t addrlen = sizeof(server_socket);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[x] Socket Error");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("[\u2714] Socket Created\n");
    }

    server_socket.sin_family = AF_INET;
    server_socket.sin_port = htons(9999);
    server_socket.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_socket, addrlen) < 0)
    {
        perror("[x] Bind error");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0)
    {
        perror("[x] Listen error");
        exit(EXIT_FAILURE);
    }

    printf("[...] Server is listening...\n");

    // Accept a new connection
    int new_sockfd;
    new_sockfd = accept(sockfd, (struct sockaddr *)&server_socket, &addrlen);

    // Receive a filename from a client
    // char buffer[25];

    // recv(new_sockfd, buffer, sizeof(buffer), 0);

    // send_file(new_sockfd, buffer);

    send_file(new_sockfd);

    close(sockfd);
    close(new_sockfd);

    return 0;
}