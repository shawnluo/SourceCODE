#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int                     server_socket_fd = 0;
    struct sockaddr_in      serv_addr;

    int                     client_socket_fd;
    socklen_t               len;
    struct sockaddr_storage addr;
    char                    ipstr[INET6_ADDRSTRLEN];
    int                     port;

    len = sizeof addr;

    char   sendBuff[1025];
    time_t ticks;

    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

	/*
		INADDR_ANY is used when you don't need to bind a socket to a specific IP. 
		When you use this value as the address when calling bind(), 
		the socket accepts connections to all the IPs of the machine.
	*/
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(5000);

    bind(server_socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(server_socket_fd, 10);

    while (1)
    {
        client_socket_fd = accept(server_socket_fd, (struct sockaddr *)&addr, &len);
        if (client_socket_fd)
        {
            if (addr.ss_family == AF_INET)
            {
                struct sockaddr_in *s = (struct sockaddr_in *)&addr;
                port = ntohs(s->sin_port);
                inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
            }
            else // AF_INET6
            {
                struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
                port = ntohs(s->sin6_port);
                inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
            }

            printf("Peer IP address: %s\n", ipstr);
            printf("Peer port: %d\n", port);
        }

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(client_socket_fd, sendBuff, strlen(sendBuff));

        close(client_socket_fd);

        sleep(1);
    }
}
