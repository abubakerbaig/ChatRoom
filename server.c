#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/in.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define MAX 10
#define PORT 5000
#define IP "127.0.0.1"

int len, sfd, cfd, i;
struct sockaddr_in caddr;
struct sockaddr_in saddr;

int main()
{
    //int n, tmp;
    //float res;
    //tmp=htonl(n);
    char cstr[25], sstr[25];

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("Socket open:\n");
        exit(1);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(IP);
    saddr.sin_port = htons(PORT);

    if (bind(sfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr)) < 0)
    {

        perror("bind open:\n");
        exit(1);
    }
    if (listen(sfd, 5) < 0)
    {

        perror("listen \n");
        exit(1);
    }
    len = sizeof(struct sockaddr_in);
    cfd = accept(sfd, (struct sockaddr *)&caddr, &len);
    while (1)
    {
        printf("Server:");

        scanf(" %[^\n]s", sstr);
        write(cfd, &sstr, sizeof(sstr));

        read(cfd, cstr, sizeof(cstr));
        printf("\nclient: %s\n", cstr);
    }
    close(sfd);
    return 0;
}
