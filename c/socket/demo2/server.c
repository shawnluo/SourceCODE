#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAXBUF    1024
/************?????********************************************
 * filename: async-server.c
 * purpose: ????????,????????
 * wrote by: zhoulifa(zhoulifa@163.com) ???(http://zhoulifa.bokee.com)
 * Linux??? Linux????? SOHO? ??? ???C??
 * date time:2007-01-25 21:22
 * Note: ??????????????????,??????????
 * ????GPL
 * Thanks to: Google.com
 * Hope:???????????????,?????????
 * ??????????????!??????????!
 *********************************************************************/

int main(int argc, char **argv)
{
    int                sockfd, new_fd;
    socklen_t          len;
    struct sockaddr_in my_addr, their_addr;
    unsigned int       myport, lisnum;
    char               buf[MAXBUF + 1];
    fd_set             rfds;
    struct timeval     tv;
    int                retval, maxfd = -1;

    if (argv[1])
    {
        myport = atoi(argv[1]);
    }
    else
    {
        myport = 7838;
    }

    if (argv[2])
    {
        lisnum = atoi(argv[2]);
    }
    else
    {
        lisnum = 2;
    }

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = PF_INET;
    my_addr.sin_port   = htons(myport);
    if (argv[3])
    {
        my_addr.sin_addr.s_addr = inet_addr(argv[3]);
    }
    else
    {
        my_addr.sin_addr.s_addr = INADDR_ANY;
    }

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))
        == -1)
    {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, lisnum) == -1)
    {
        perror("listen");
        exit(1);
    }

    while (1)
    {
        printf
            ("\n----waiting for new connection ……\n");
        len = sizeof(struct sockaddr);
        if ((new_fd =
                 accept(sockfd, (struct sockaddr *)&their_addr,
                        &len)) == -1)
        {
            perror("accept");
            exit(errno);
        }
        else
        {
            printf("server: got connection from %s, port %d, socket %d\n",
                   inet_ntoa(their_addr.sin_addr),
                   ntohs(their_addr.sin_port), new_fd);
        }

        /* new connection data recv and send */
        printf("\n get ready, so we can chat.....input message directly, and press return to send message\n");
        while (1)
        {
            /* enmpty the collection */
            FD_ZERO(&rfds);
            /* add standard input handler 0 into collection */
            FD_SET(0, &rfds);
            maxfd = 0;
            /* add the current connection handler new_fd to the collection */
            FD_SET(new_fd, &rfds);
            if (new_fd > maxfd)
            {
                maxfd = new_fd;
            }
            /* set up MAX waiting time */
            tv.tv_sec  = 1;
            tv.tv_usec = 0;
            /* start to waiting */
            retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
            if (retval == -1)
            {
                printf("will exit,select error! %s", strerror(errno));
                break;
            }
            else if (retval == 0)
            {
                /* printf
                 * ("no messages are coming, user didn't press any keys, continue waiting ……\n"); */
                continue;
            }
            else
            {
                if (FD_ISSET(0, &rfds))
                {
                    /* user press keys, read input and send it away */
                    bzero(buf, MAXBUF + 1);
                    fgets(buf, MAXBUF, stdin);
                    if (!strncasecmp(buf, "quit", 4))
                    {
                        printf("request to stop chat!\n");
                        break;
                    }
                    len = send(new_fd, buf, strlen(buf) - 1, 0);
                    if (len > 0)
                    {
                        printf
                            ("message:%s\t send succefully,totally sent %d bytes!\n",
                            buf, len);
                    }
                    else
                    {
                        printf
                            ("message'%s'send fail!error code is %d,error message is'%s'\n",
                            buf, errno, strerror(errno));
                        break;
                    }
                }
                if (FD_ISSET(new_fd, &rfds))
                {
                    /* current connected socket receved message */
                    bzero(buf, MAXBUF + 1);
                    /* receive client message */
                    len = recv(new_fd, buf, MAXBUF, 0);
                    if (len > 0)
                    {
                        printf
                            ("receive message successfully:'%s',totally %d bytes data\n",
                            buf, len);
                    }
                    else
                    {
                        if (len < 0)
                        {
                            printf
                                ("message receive failed!error code is%d,error message is'%s'\n",
                                errno, strerror(errno));
                        }
                        else
                        {
                            printf("client exit,stopping chat now\n");
                        }
                        break;
                    }
                }
            }
        }
        close(new_fd);
        /* handle every new connection data recv and send */
        printf("still want to talk to other connection(no->Exit)");
        fflush(stdout);
        bzero(buf, MAXBUF + 1);
        fgets(buf, MAXBUF, stdin);
        if (!strncasecmp(buf, "no", 2))
        {
            printf("stopping chat!\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
