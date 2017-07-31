#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAXBUF    1024
/************?????********************************************
 * // *filename: ssync-client.c
 * purpose: ????????,???????
 * wrote by: zhoulifa(zhoulifa@163.com) ???(http://zhoulifa.bokee.com)
 * Linux??? Linux????? SOHO? ??? ???C??
 * date time:2007-01-25 21:32
 * Note: ??????????????????,??????????
 * ????GPL
 * Thanks to: Google.com
 * Hope:???????????????,?????????
 * ??????????????!??????????!
 *********************************************************************/
int main(int argc, char **argv)
{
    int                sockfd, len;
    struct sockaddr_in dest;
    char               buffer[MAXBUF + 1];
    fd_set             rfds;
    struct timeval     tv;
    int                retval, maxfd = -1;

    if (argc != 3)
    {
        printf
            ("wrong usage!the right usage:\n\t\t%s IP address port\n\t for example:\t%s 127.0.0.1 80\n this program is used to receive no more than MAXBUF bytes message from one IP address one port",
            argv[0], argv[0]);
        exit(0);
    }
    /* create a socket for tcp communication */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket");
        exit(errno);
    }

    /* Inite server address and port */
    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port   = htons(atoi(argv[2]));
    if (inet_aton(argv[1], (struct in_addr *)&dest.sin_addr.s_addr) == 0)
    {
        perror(argv[1]);
        exit(errno);
    }

    /* connect to server */
    if (connect(sockfd, (struct sockaddr *)&dest, sizeof(dest)) != 0)
    {
        perror("Connect ");
        exit(errno);
    }

    printf
        ("\n get ready to chat...just input message and return key to send message\n");
    while (1)
    {
        /* empty collection */
        FD_ZERO(&rfds);
        /*  */
        FD_SET(0, &rfds);
        maxfd = 0;
        /*  */
        FD_SET(sockfd, &rfds);
        if (sockfd > maxfd)
        {
            maxfd = sockfd;
        }
        /*  */
        tv.tv_sec  = 1;
        tv.tv_usec = 0;
        /*  */
        retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
        if (retval == -1)
        {
            printf("EXIT,select is wrong! %s", strerror(errno));
            break;
        }
        else if (retval == 0)
        {
            /* printf
             * ("no message is coming, user didn't press keys, so continue waiting……\n"); */
            continue;
        }
        else
        {
            if (FD_ISSET(sockfd, &rfds))
            {
                /* if there are message on connected socket, then receive message and show */
                bzero(buffer, MAXBUF + 1);
                /* receive messag, no more than MAXBUF bytes */
                len = recv(sockfd, buffer, MAXBUF, 0);
                if (len > 0)
                {
                    printf
                        ("recived message:'%s', totally %d bytes data\n",
                        buffer, len);
                }
                else
                {
                    if (len < 0)
                    {
                        printf
                            ("message receive failed! wrong code is %d, wrong message is'%s'\n",
                            errno, strerror(errno));
                    }
                    else
                    {
                        printf("server exit,stop chat!\n");
                    }
                    break;
                }
            }
            if (FD_ISSET(0, &rfds))
            {
                /* user pressed keys, send the inputs */
                bzero(buffer, MAXBUF + 1);
                fgets(buffer, MAXBUF, stdin);
                if (!strncasecmp(buffer, "quit", 4))
                {
                    printf("myself request stop chat!\n");
                    break;
                }
                /* send message to server */
                len = send(sockfd, buffer, strlen(buffer) - 1, 0);
                if (len < 0)
                {
                    printf
                        ("message '%s' failed! error code is %d, error message is'%s'\n",
                        buffer, errno, strerror(errno));
                    break;
                }
                else
                {
                    printf
                        ("message:%s\t send successfully, totally %d were sent!\n",
                        buffer, len);
                }
            }
        }
    }
    /* ???? */
    close(sockfd);
    return 0;
}
