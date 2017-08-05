#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define BUF_SIZE    500

int clientMode = 0;

typedef struct parameter
{
    char *ipAddress;
    char *port;
} *PARA;

#define PARA_LEN    sizeof(struct parameter)

void *Run_clientMode(void *arg)
{
    PARA               info = (PARA)arg;
	
    int                clientSocket, n, option = 1;
    char               buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t          addr_size;

//	PARA info = (PARA)arg;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(1));

    serverAddr.sin_family = AF_INET;

    serverAddr.sin_port = htons(atoi(info->port));
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr(info->ipAddress);
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size) == 0)
    {
        clientMode = 1;
        printf("Running in client mode\n");
    }
    else
    {
        printf("return in thread\n");
        return NULL;
    }


    while (1)
    {
        printf("Please enter the message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        n = write(clientSocket, buffer, strlen(buffer));
        if (n < 0)
        {
            error("ERROR writing to socket");
        }

	    /*---- Read the message from the server into the buffer ----*/
	    recv(clientSocket, buffer, 1024, 0);
	    printf("Data received: %s\n", buffer);
    }
    return 0;
}



#if 0
{
    int                sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent     *server;

    PARA               info = (PARA)arg;

    char               buffer[256];

/*	if (argc < 3) {
 *         fprintf(stderr,"usage %s hostname port\n", argv[0]);
 *         exit(0);
 *      }*/
    portno = atoi(info->port);
    printf("portno = %d\t  ipaddress = \n", portno);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    server = gethostbyname(info->ipAddress);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }
    clientMode = 1;

    while (1)
    {
        printf("Please enter the message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
        {
            error("ERROR writing to socket");
        }
    }

#if 0
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        error("ERROR reading from socket");
    }
    printf("%s\n", buffer);
#endif
    close(sockfd);
    return 0;
}

{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int             sfd, s, j;
    size_t          len;
    ssize_t         nread;
    char            buf[BUF_SIZE];

    PARA            info = (PARA)arg;

    int             n;

#if 0
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
#endif
    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family   = AF_UNSPEC;  /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags    = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    s = getaddrinfo(info->ipAddress, info->port, &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
     *  Try each address until we successfully connect(2).
     *  If socket(2) (or connect(2)) fails, we (close the socket
     *  and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
        {
            continue;
        }

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
        {
            printf(" addr = %s\n", (struct sockaddr_in *)rp->ai_addr);
            break;                  /* Success */
        }
        close(sfd);
    }

    if (rp == NULL)                /* No address succeeded */
    {
        fprintf(stderr, "Could not connect\n");
        pthread_exit(0);
    }
    clientMode = 1;

    freeaddrinfo(result);          /* No longer needed */

    /* Send remaining command-line arguments as separate
     *  datagrams, and read responses from server */

#if 0
    for (j = 3; j < argc; j++)
    {
        len = strlen(argv[j]) + 1;
        /* +1 for terminating null byte */

        if (len + 1 > BUF_SIZE)
        {
            fprintf(stderr,
                    "Ignoring long message in argument %d\n", j);
            continue;
        }

        if (write(sfd, argv[j], len) != len)
        {
            fprintf(stderr, "partial/failed write\n");
            exit(EXIT_FAILURE);
        }

        nread = read(sfd, buf, BUF_SIZE);
        if (nread == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Received %ld bytes: %s\n", (long)nread, buf);
    }
#endif
    while (1)
    {
        bzero(buf, 256);
        fgets(buf, 255, stdin);
        n = write(sfd, buf, len);
        if (n < 0)
        {
            error("ERROR writing to socket");
        }
#if 0
        bzero(buf, 256);
        n = read(sfd, buf, BUF_SIZE);
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("%s\n", buf);
#endif
    }
    close(sfd);
}
#endif

void Run_serverMode(PARA para)
{
    int                sockfd, newsockfd, portno, clilen, option = 1;
    char               buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int                n;

//	PARA info = para;


/*	if (argc < 2)
 *      {
 *              fprintf(stderr, "ERROR, no port provided\n");
 *              exit(1);
 *      }*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(1));
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno                    = atoi(para->port);
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port        = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    listen(sockfd, 5);
    clilen    = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }
    while (1)
    {
		bzero(buffer, 256);
        n = recv(newsockfd, buffer, 255, 0);//read() is equivalent to recv() with a flags parameter of 0.
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("Here is the message: %s\n", buffer);

		
		printf("Please enter the message: ");
		bzero(buffer, 256);
		fgets(buffer, 255, stdin);
        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0)
        {
            error("ERROR writing to socket");
        }

#if 0
	{
			printf("Please enter the message: ");
			bzero(buffer, 256);
			fgets(buffer, 255, stdin);
			n = write(clientSocket, buffer, strlen(buffer));
			if (n < 0)
			{
				error("ERROR writing to socket");
			}
	
			/*---- Read the message from the server into the buffer ----*/
			recv(clientSocket, buffer, 1024, 0);
			printf("Data received: %s\n", buffer);
		}
#endif



		
    }
    close(sockfd);
    return 0;
}


int main(int argc, char *argv[])
{
//	./chat 192.168.0.104 8888
//1. creating a thread for running as client mode.
//2. setting a timer in main(). if client thread connected successfully in 3 seconds. then keeping client mode.
//3. if not, then starts server mode in main().

    PARA para = (PARA)malloc(PARA_LEN);

    para->ipAddress = argv[1];
    para->port      = argv[2];


    pthread_t tidClie[255];

    pthread_create(&tidClie[0], NULL, Run_clientMode, (void *)para);

    sleep(3);

    if (clientMode == 1)        //run as client mode.
    {
//        printf("Running in client mode\n");
        while (1)
        {
            sleep(5);
        }
    }
    else
    {
        pthread_cancel(tidClie[0]);             //stop client mode.

        printf("Running in server mode\n");
        Run_serverMode(para);

        pthread_join(tidClie[0], NULL);
    }

	free(para);

    return 0;
}
