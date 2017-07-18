#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define PORT        8888
#define BACKLOG     10
#define MAXCONN     100
#define BUFFSIZE    1024
typedef unsigned char   BYTE;
typedef struct ClientInfo
{
    struct sockaddr_in addr;
    int                clientfd;
    int                isConn;
    int                index;
} ClientInfo;
pthread_mutex_t activeConnMutex;
pthread_mutex_t clientsMutex[MAXCONN];
pthread_cond_t  connDis;
pthread_t       threadID[MAXCONN];
pthread_t       serverManagerID;
ClientInfo      clients[MAXCONN];
int             serverExit = 0;
/*@brief Transform the all upper case
 *
 */
void tolowerString(char *s)
{
    int i = 0;

    while (i < strlen(s))
    {
        s[i] = tolower(s[i]);
        ++i;
    }
}
void listAll(char *all)
{
    int i = 0, len = 0;

    len += sprintf(all + len, "Index   \t\tIP Address   \t\tPort\n");
    for ( ; i < MAXCONN; ++i)
    {
        pthread_mutex_lock(&clientsMutex[i]);
        if (clients[i].isConn)
        {
            len += sprintf(all + len, "%.8d\t\t%s\t\t%d\n", clients[i].index, inet_ntoa(clients[i].addr.sin_addr), clients[i].addr.sin_port);
        }
        pthread_mutex_unlock(&clientsMutex[i]);
    }
}
void clientManager(void *argv)
{
    ClientInfo         *client = (ClientInfo *)(argv);

    BYTE               buff[BUFFSIZE];
    int                recvbytes;

    int                i           = 0;
    int                clientfd    = client->clientfd;
    struct sockaddr_in addr        = client->addr;
    int                isConn      = client->isConn;
    int                clientIndex = client->index;

    while ((recvbytes = recv(clientfd, buff, BUFFSIZE, 0)) != -1)
    {
        //   buff[recvbytes] = '\0';
        tolowerString(buff);    //case-insensitive

        char cmd[100];
        if ((sscanf(buff, "%s", cmd)) == -1)    //command error
        {
            char err[100];
            if (send(clientfd, err, strlen(err) + 1, 0) == -1)
            {
                strcpy(err, "Error command and please enter again!\n");
                fprintf(stdout, "%d sends an eroor command\n", clientfd);
                break;
            }
        }
        else
        {
            char msg[BUFFSIZE];       //The message content
            int  dest  = clientIndex; //message destination
            int  isMsg = 0;           //any message needed to send
            if (strcmp(cmd, "disconn") == 0)
            {
                pthread_cond_signal(&connDis);  //send a disconnetion signal and the waiting client can get response
                break;
            }
            else if (strcmp(cmd, "time") == 0)
            {
                time_t    now;
                struct tm *timenow;
                time(&now);
                timenow = localtime(&now);
                strcpy(msg, asctime(timenow));
                isMsg = 1;
            }
            else if (strcmp(cmd, "name") == 0)
            {
                strcpy(msg, "MACHINE NAME");
                isMsg = 1;
            }
            else if (strcmp(cmd, "list") == 0)
            {
                listAll(msg);
                isMsg = 1;
            }
            else if (strcmp(cmd, "send") == 0)
            {
                if (sscanf(buff + strlen(cmd) + 1, "%d%s", &dest, msg) == -1 || dest >= MAXCONN)
                {
                    char err[100];
                    strcpy(err, "Destination ID error and please use list to check and enter again!\n");
                    fprintf(stderr, "Close %d client eroor: %s(errno: %d)\n", clientfd, strerror(errno), errno);
                    break;
                }
                fprintf(stdout, "%d %s\n", dest, msg);
                isMsg = 1;
            }
            else
            {
                char err[100];
                strcpy(err, "Unknown command and please enter again!\n");
                fprintf(stderr, "Send to %d message eroor: %s(errno: %d)\n", clientfd, strerror(errno), errno);
                break;
            }


            if (isMsg)
            {
                pthread_mutex_lock(&clientsMutex[dest]);
                if (clients[dest].isConn == 0)
                {
                    sprintf(msg, "The destination is disconneted!");
                    dest = clientIndex;
                }

                if (send(clients[dest].clientfd, msg, strlen(msg) + 1, 0) == -1)
                {
                    fprintf(stderr, "Send to %d message eroor: %s(errno: %d)\n", clientfd, strerror(errno), errno);
                    pthread_mutex_unlock(&clientsMutex[dest]);
                    break;
                }
                printf("send successfully!\n");
                pthread_mutex_unlock(&clientsMutex[dest]);
            }
        }  //end else
    }   //end while

    pthread_mutex_lock(&clientsMutex[clientIndex]);
    client->isConn = 0;
    pthread_mutex_unlock(&clientsMutex[clientIndex]);

    if (close(clientfd) == -1)
    {
        fprintf(stderr, "Close %d client eroor: %s(errno: %d)\n", clientfd, strerror(errno), errno);
    }
    fprintf(stderr, "Client %d connetion is closed\n", clientfd);

    pthread_exit(NULL);
}

void serverManager(void *argv)
{
    while (1)
    {
        char cmd[100];
        scanf("%s", cmd);
        tolowerString(cmd);
        if (strcmp(cmd, "exit") == 0)
        {
            serverExit = 1;
        }
        else if (strcmp(cmd, "list") == 0)
        {
            char buff[BUFFSIZE];
            listAll(buff);
            fprintf(stdout, "%s", buff);
        }
        else if (strcmp(cmd, "kill") == 0)
        {
            int clientIndex;
            scanf("%d", &clientIndex);
            if (clientIndex >= MAXCONN)
            {
                fprintf(stderr, "Unkown client!\n");
                continue;
            }
            pthread_mutex_lock(&clientsMutex[clientIndex]);
            if (clients[clientIndex].isConn)
            {
                if (close(clients[clientIndex].clientfd) == -1)
                {
                    fprintf(stderr, "Close %d client eroor: %s(errno: %d)\n", clients[clientIndex].clientfd, strerror(errno), errno);
                }
            }
            else
            {
                fprintf(stderr, "Unknown client!\n");
            }
            pthread_mutex_unlock(&clientsMutex[clientIndex]);
            pthread_cancel(threadID[clientIndex]);
        }
        else
        {
            fprintf(stderr, "Unknown command!\n");
        }
    }
}

int main()
{
    int activeConn = 0;

    //initialize the mutex
    pthread_mutex_init(&activeConnMutex, NULL);
    pthread_cond_init(&connDis, NULL);
    int i = 0, option = 1;;
    for ( ; i < MAXCONN; ++i)
    {
        pthread_mutex_init(&clientsMutex[i], NULL);
    }

    for (i = 0; i < MAXCONN; ++i)
    {
        clients[i].isConn = 0;
    }

    //create the server manager thread
    pthread_create(&serverManagerID, NULL, (void *)(serverManager), NULL);


    int                listenfd;
    struct sockaddr_in servaddr;

    //create a socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "Create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    else
    {
        fprintf(stdout, "Create a socket successfully\n");
    }

    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(1));


    fcntl(listenfd, F_SETFL, O_NONBLOCK);      //set the socket non-block

    //set the server address
    memset(&servaddr, 0, sizeof(servaddr));       //initialize the server address
    servaddr.sin_family      = AF_INET;           //AF_INET means using TCP protocol
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //any in address(there may more than one network card in the server)
    servaddr.sin_port        = htons(PORT);       //set the port

    //bind the server address with the socket
    if (bind(listenfd, (struct sockaddr *)(&servaddr), sizeof(servaddr)) == -1)
    {
        fprintf(stderr, "Bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    else
    {
        fprintf(stdout, "Bind socket successfully\n");
    }

    //listen
    if (listen(listenfd, BACKLOG) == -1)
    {
        fprintf(stderr, "Listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    else
    {
        fprintf(stdout, "Listen socket successfully\n");
    }


    while (1)
    {
        if (serverExit)
        {
            for (i = 0; i < MAXCONN; ++i)
            {
                if (clients[i].isConn)
                {
                    if (close(clients[i].clientfd) == -1)       //close the client
                    {
                        fprintf(stderr, "Close %d client eroor: %s(errno: %d)\n", clients[i].clientfd, strerror(errno), errno);
                    }
                    if (pthread_cancel(threadID[i]) != 0)       //cancel the corresponding client thread
                    {
                        fprintf(stderr, "Cancel %d thread eroor: %s(errno: %d)\n", (int)(threadID[i]), strerror(errno), errno);
                    }
                }
            }
            return 0;   //main exit;
        }

        pthread_mutex_lock(&activeConnMutex);
        if (activeConn >= MAXCONN)
        {
            pthread_cond_wait(&connDis, &activeConnMutex);
        }
        pthread_mutex_unlock(&activeConnMutex);

        //find an empty postion for a new connnetion
        int i = 0;
        while (i < MAXCONN)
        {
            pthread_mutex_lock(&clientsMutex[i]);
            if (!clients[i].isConn)
            {
                pthread_mutex_unlock(&clientsMutex[i]);
                break;
            }
            pthread_mutex_unlock(&clientsMutex[i]);
            ++i;
        }

        //accept
        struct sockaddr_in addr;
        int                clientfd;
        int                sin_size = sizeof(struct sockaddr_in);
        if ((clientfd = accept(listenfd, (struct sockaddr *)(&addr), &sin_size)) == -1)
        {
            sleep(1);
            //fprintf(stderr, "Accept socket error: %s(errno: %d)\n", strerror(errno), errno);
            continue;
            //exit(0);
        }
        else
        {
            fprintf(stdout, "Accept socket successfully\n");
        }

        pthread_mutex_lock(&clientsMutex[i]);
        clients[i].clientfd = clientfd;
        clients[i].addr     = addr;
        clients[i].isConn   = 1;
        clients[i].index    = i;
        pthread_mutex_unlock(&clientsMutex[i]);

        //create a thread for a client
        pthread_create(&threadID[i], NULL, (void *)clientManager, &clients[i]);
    }   //end-while
}
