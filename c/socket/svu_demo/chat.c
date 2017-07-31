/* A simple server in the internet domain using TCP
 * The port number is passed as an argument */
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

typedef struct
{
	char *ipaddress;
	int port;
} *PARA;



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
char *getLocalDevice()
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
    }
    fclose(arpCache);
    //return 0;

	return ipAddr;
}




void *client(void *arg)
{
    int                sockfd, portno, n, option = 1;

    struct sockaddr_in serv_addr;
    struct hostent     *server;

    char               buffer[256];

    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = (int)arg;//atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(1));

    server = gethostbyname(argv[1]);
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



int main(int argc, char *argv[])
{
    int                sockfd, newsockfd, portno, clilen, option = 1;
    char               buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int                n;
	PARA para = (PARA)malloc(sizeof(PARA));
	para->ipaddress = argv[1];
	para->port = atoi(argv[2]);

//    pthread_t tidServ;
    pthread_t tidClie;

//    pthread_create(&tidServ, NULL, server, NULL);
    pthread_create(&tidClie, NULL, client, (void *)argv[0]);

//    pthread_join(tidServ, NULL);

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


    pthread_join(tidClie, NULL);
	
    return 0;
}

