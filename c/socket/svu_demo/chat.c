/* A simple server in the internet domain using TCP
 * The port number is passed as an argument */

/*	
	./chat 8888

	1. the app sets itself to be a client;
	2. get ip addresses by scanning local ARP cache;
	3. trying to connect the devices as a client;
	4. if it fails in 3 seconds, then converts itself to be a server;
	5. 
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>


int clientMode = 0;

void error(char *msg)
{
    perror(msg);
    exit(1);
}

typedef struct arp_device
{
	char ipAddress[255][1024];
	int count;
}*ARP_Device;

typedef struct dev
{
	char *Dev_ipaddress;
	int port;
}*DEV;

#define ARP_Len sizeof(struct arp_device)

#define xstr(s)    str(s)
#define str(s)     #s

#define ARP_CACHE          "/proc/net/arp"
#define ARP_STRING_LEN     1023
#define ARP_BUFFER_LEN     (ARP_STRING_LEN + 1)

/* Format for fscanf() to read the 1st, 4th, and 6th space-delimited fields */
#define ARP_LINE_FORMAT    "%" xstr(ARP_STRING_LEN) "s %*s %*s " \
    "%" xstr(ARP_STRING_LEN) "s %*s "                            \
    "%" xstr(ARP_STRING_LEN) "s"


/********************************************
 *
 ********************************************/
 
ARP_Device getLocalDevice(ARP_Device deviceInfo)
{
    FILE *arpCache = fopen(ARP_CACHE, "r");

    if (!arpCache)
    {
        perror("Arp Cache: Failed to open file \"" ARP_CACHE "\"");
        return 1;
    }

    /* Ignore the first line, which contains the header */
    char header[ARP_BUFFER_LEN];
    if (!fgets(header, sizeof(header), arpCache))
    {
        return 1;
    }

    char ipAddr[ARP_BUFFER_LEN], hwAddr[ARP_BUFFER_LEN], device[ARP_BUFFER_LEN];
    int  count = 0;
    while (3 == fscanf(arpCache, ARP_LINE_FORMAT, ipAddr, hwAddr, device))	//return 3 since there are 3 varialble 
    {
        printf("%03d: Mac Address of [%s] on [%s] is \"%s\"\n",
               ++count, ipAddr, device, hwAddr);
		
		memset(deviceInfo->ipAddress[count], '0', 1024);
		strcpy(deviceInfo->ipAddress[count], ipAddr);
		deviceInfo->count++;
    }
		
    fclose(arpCache);
	
    return deviceInfo;
}


void *client(void *arg)
{
    int                sockfd, portno, n, option = 1;

    struct sockaddr_in serv_addr;
    struct hostent     *server;

    char               buffer[256];
	strcpy(serv_addr, (DEV)arg->Dev_ipaddress);
    portno = atoi(arg[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(1));


    //server = gethostbyname(argv[1]);
    server = 
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
	
    printf("Please enter the message: ");
    while (1)
    {
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
        {
            error("ERROR writing to socket");
        }
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("%s\n", buffer);
    }
	
    pthread_exit((void *)0);
}


void *client_ext(void *arg)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int             sfd, s, j;
    size_t          len;
    ssize_t         nread;
    char            buf[BUF_SIZE];

	DEV myinfo = (DEV)arg;
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

    s = getaddrinfo(myinfo->Dev_ipaddress, myinfo->port, &hints, &result);
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
			clientMode = 1;
            break;                  /* Success */
        }
        close(sfd);
    }

    if (rp == NULL)                /* No address succeeded */
    {
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);          /* No longer needed */

    /* Send remaining command-line arguments as separate
     *  datagrams, and read responses from server */

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

    exit(EXIT_SUCCESS);
}




int main(int argc, char *argv[])
{
    int                sockfd, newsockfd, portno, clilen, option = 1;
    char               buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int                n, i;
	DEV thread_para;
	PARA para = (PARA)malloc(sizeof(PARA));
	para->ipaddress = argv[1];
	para->port = atoi(argv[2]);
    pthread_t tidClie[255];

	ARP_Device arpDevice = (ARP_Device)malloc(ARP_Len);

	getLocalDevice(arpDevice);

	thread_para->port = atoi(argv[1]);
	
	if(arpDevice->count > 0)
	{
		
		for(i = 0; i < arpDevice->count; i++)
		{
			strcpy(thread_para->Dev_ipaddress, arpDevice->ipAddress[i]);
    		pthread_create(&tidClie[i], NULL, client_ext, (void *)thread_para);
		}
		sleep(3);

		if(clientMode == 1)
		{
			while(1)
			{
				sleep(1);
			}
		}
		else
		{
			pthread_cancel(&tidClie);
		}
	}

    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(1));
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno                    = atoi(argv[0]);
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

	clientMode = 1;
    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }
    while (1)
    {
        bzero(buffer, 256);
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

	if(arpDevice->count > 0)
	{
		for(i = 0; i < arpDevice->count; i++)
		{
	    	pthread_join(tidClie[i], NULL);
		}
	}		
    return 0;
}

