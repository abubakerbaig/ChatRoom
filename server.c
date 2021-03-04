#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/in.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 5000
//#define IP "192.168.43.2"
#define MAX_SIZE 100

pthread_t incoming_h, outgoing_h;
pthread_attr_t incoming_attr, outgoing_attr;


int len, sfd, cfd, i;
struct sockaddr_in caddr;
struct sockaddr_in saddr;
char cstr[MAX_SIZE], sstr[MAX_SIZE];

int my_atoi(char a)
{
    return a - 48;
}

int validate_ip(const char *ip)
{
    printf("validating %s...\n", ip);
    int dots = 0;
    for (int i = 0; ip[i] != '\0'; i++)
    {
        if (((my_atoi(ip[i]) >= 0) && (my_atoi(ip[i]) <= 9)) || (ip[i] == '.'))
        {
            if (ip[i] == '.')
            {
                dots++;
            }
            
        }
        else
        {
            return 1;
        }
    }
    if (dots != 3)
    {
        return 1;
    }
    return 0;
}

void  *incoming(void *arg)    {
    while(1)    {
        read(cfd, cstr, sizeof(cstr));
        printf("\nclient: %s\n", cstr);    
    }
} 

void  *outgoing(void *arg)    {
    while(1)    {
        printf("Server:");
        scanf(" %[^\n]s", sstr);
        write(cfd, &sstr, sizeof(sstr));

    }
} 

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Please enter IP addresses as a argument..\n");
        return 0;
    }
    if (validate_ip(argv[1]))
    {
        printf("ERROR: Enter Valid IP address\n");
        return 0;
    }
    printf("socket initilizing.....\n");
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("Socket open:\n");
        exit(1);
    }
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_port = htons(PORT);
    printf("Binding with %s...\n", argv[1]);
    if (bind(sfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr)) < 0)
    {
        perror("bind open:\n");
        exit(1);
    }

    printf("Listening\n");
    if (listen(sfd, 5) < 0)
    {
        perror("listen \n");
        exit(1);
    }
    len = sizeof(struct sockaddr_in);
    printf("Waiting to accept\n");
    cfd = accept(sfd, (struct sockaddr *)&caddr, &len);
    
    pthread_create(&incoming_h, &incoming_attr, incoming, NULL);
    pthread_create(&outgoing_h, &outgoing_attr, outgoing, NULL);
    pthread_join(incoming_h, NULL);
    pthread_join(outgoing_h, NULL);

    close(sfd);
    return 0;
}