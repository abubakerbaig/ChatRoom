#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/in.h>

#define MAX 10

int cfd, n;
struct sockaddr_in saddr;
int len;

int main(int argc, char const *argv[])
{
       //int n, temp;
       //float res = 0;
       char sstr[25], cstr[25];
       cfd = socket(AF_INET, SOCK_STREAM, 0);
       if (cfd < 0)
       {
              perror("Socket open:\n");
              exit(1);
       }
       saddr.sin_family = AF_INET;
       saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
       saddr.sin_port = htons(5000);

       if (connect(cfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) < 0)
       {
              perror("Connet error:\n");
              exit(1);
       }
       while (1)
       {
              read(cfd, &sstr, sizeof(sstr));
              printf("server : %s\n", sstr);

              printf("\nclient:");
              scanf(" %[^\n]s", cstr);
              write(cfd, &cstr, sizeof(cstr));
       }
       close(cfd);
       return 0;
}
