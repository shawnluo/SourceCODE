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

#define PARA_LEN sizeof(struct parameter)

void *Run_clientMode(void *arg)
{	
	struct addrinfo hints;
    struct addrinfo *result, *rp;
    int             sfd, s, j;
    size_t          len;
    ssize_t         nread;
    char            buf[BUF_SIZE];

	PARA info = (PARA)arg;

	int n;

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
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
        {
            continue;
        }

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
        {
            break;                  /* Success */
        }
        close(sfd);
    }

    if (rp == NULL)                /* No address succeeded */
    {
		clientMode = 1;
        fprintf(stderr, "Could not connect\n");
		pthread_exit(0);
    }

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
        bzero(buf, 256);
        n = read(sfd, buf, BUF_SIZE);
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("%s\n", buf);
    }
	close(sfd);

	
}

void Run_serverMode(PARA para)
{
	struct addrinfo 		hints;
	struct addrinfo 		*result, *rp;
	int 					sfd, s;
	struct sockaddr_storage peer_addr;
	socklen_t				peer_addr_len;
	ssize_t 				nread;
	char					buf[BUF_SIZE];

	char *port = para->port;

#if 0
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}
#endif
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family    = AF_UNSPEC;  /* Allow IPv4 or IPv6 */
	hints.ai_socktype  = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags	   = AI_PASSIVE; /* For wildcard IP address */
	hints.ai_protocol  = 0; 		 /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr	   = NULL;
	hints.ai_next	   = NULL;

	s = getaddrinfo(NULL, port, &hints, &result);
	if (s != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	 *	Try each address until we successfully bind(2).
	 *	If socket(2) (or bind(2)) fails, we (close the socket
	 *	and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket(rp->ai_family, rp->ai_socktype,
					 rp->ai_protocol);
		if (sfd == -1)
		{
			continue;
		}

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
		{
			break;					/* Success */
		}
		close(sfd);
	}

	if (rp == NULL) 			   /* No address succeeded */
	{
		fprintf(stderr, "Could not bind\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);		   /* No longer needed */

	/* Read datagrams and echo them back to sender */

	for ( ; ; )
	{
		peer_addr_len = sizeof(struct sockaddr_storage);
		nread		  = recvfrom(sfd, buf, BUF_SIZE, 0,
								 (struct sockaddr *)&peer_addr, &peer_addr_len);
		if (nread == -1)
		{
			continue;				/* Ignore failed request */
		}
		char host[NI_MAXHOST], service[NI_MAXSERV];

		s = getnameinfo((struct sockaddr *)&peer_addr,
						peer_addr_len, host, NI_MAXHOST,
						service, NI_MAXSERV, NI_NUMERICSERV);
		if (s == 0)
		{
			printf("Received %ld bytes from %s:%s\n",
				   (long)nread, host, service);
		}
		else
		{
			fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
		}
#if 0
		if (sendto(sfd, buf, nread, 0,
				   (struct sockaddr *)&peer_addr,
				   peer_addr_len) != nread)
		{
			fprintf(stderr, "Error sending response\n");
		}
#endif
	}

#if 0	
    while (1)
    {
        bzero(buf, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("Here is the message: %s\n", buffer);
        n = write(newsockfd, "I got your message", 18);
        if (n < 0)
        {
            error("ERROR writing to socket");
        }
    }
    close(sockfd);
#endif	
}


int main(int argc, char *argv[])
{
//	./chat 192.168.0.104 8888
//1. creating a thread for running as client mode.
//2. setting a timer in main(). if client thread connected successfully in 3 seconds. then keeping client mode.
//3. if not, then starts server mode in main().

	PARA para = (PARA)malloc(PARA_LEN);
	para->ipAddress = argv[1];
	para->port = argv[2];
	

	pthread_t tidClie[255];

	pthread_create(&tidClie[0], NULL, Run_clientMode, (void *)para);

	sleep(3);

	if(clientMode == 1)	//run as client mode.
	{
		printf("Running in client mode\n");
		while(1)
		{
			sleep(5);
		}
	}
	
	pthread_cancel(tidClie[0]);	//stop client mode.
	
	printf("Running in server mode\n");
	Run_serverMode(para);

	pthread_join(tidClie[0], NULL);
	return 0;
}
