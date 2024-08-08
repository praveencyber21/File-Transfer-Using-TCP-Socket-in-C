//  File transfer using tcp - Client program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024

void receive_file(int sockfd)
{
    FILE *fp = fopen("receive.txt", "a");

    char buffer[SIZE];
    // recv(sockfd, buffer, sizeof(buffer), 0);

    // if (sizeof(buffer) != 0)
    // {
    //     printf("%s\n", buffer);
    //     exit(EXIT_FAILURE);
    // }
    ssize_t datareceived; // Stores the number bytes received from the socket
    while ((datareceived = recv(sockfd, buffer, sizeof(buffer), 0)) > 0)
    {

        buffer[datareceived] = '\0';
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    if (datareceived < 0)
    {
        perror("[x] Error receving data");
    }

    printf("[\u2714] File receive successfully\n");

    fclose(fp);
    close(sockfd);
}

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in client_address;
    socklen_t addrlen = sizeof(client_address);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[x] Socket error");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("[\u2714] Socket created\n");
    }
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9999);
    client_address.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&client_address, addrlen) < 0)
    {
        perror("[x] Server is not ready");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("[\u2714] Successfully connected with server\n");
    }

    // // Get the filename from the user
    // char filename[25];

    // printf("Enter file  name: ");
    // scanf(" [%^\n]s", filename);

    // receive_file(sockfd, filename);

    receive_file(sockfd);

    close(sockfd);

    return 0;
}