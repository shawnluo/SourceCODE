#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/socket.h>
void main()
{
    struct addrinfo    *ailist, *aip;
    struct addrinfo    hint;
    struct sockaddr_in *sinp;
    char               *hostname = "localhost.localdomain"; /*this is my hostname, just type "hostname" in terminal*/
    char               buf[INET_ADDRSTRLEN];
    char               *server = "3294";          /*this is port*/
    const char         *addr;
    int                ilRc;

    hint.ai_family    = AF_UNSPEC;  /* hint setting */
    hint.ai_socktype  = 0;//SOCK_DGRAM;          /* socket type. like SOCK_DGRAM */
    hint.ai_flags     = AI_PASSIVE; /* flags. like AI_CANONNAME; */
    hint.ai_protocol  = 0;          /* default value is 0 */
    hint.ai_addrlen   = 0;          /* dont modify below, set value 0 or NULL */
    hint.ai_canonname = NULL;
    hint.ai_addr      = NULL;
    hint.ai_next      = NULL;
    ilRc              = getaddrinfo(hostname, server, &hint, &ailist);
    if (ilRc < 0)
    {
        char str_error[100];
        strcpy(str_error, gai_strerror(errno));
        printf("str_error = %s", str_error);
        return;
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next) /* show the getting value */
    {
        sinp = (struct sockaddr_in *)aip->ai_addr;      /* why for? look down pls */
        addr = inet_ntop(AF_INET, &sinp->sin_addr, buf, INET_ADDRSTRLEN);
        printf(" addr = %s", addr ? addr : "unknow ");
        printf("port = %d ", ntohs(sinp->sin_port));
        printf(" \n");
    }
}
