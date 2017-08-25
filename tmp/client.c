/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
 
int main(int argc , char *argv[])
{
    int sock, i;
    struct sockaddr_in server;
    char message[6000] , server_reply[2000];
	char tt[100];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");		//using server's ip address. or using localhost ip address 127.0.0.1
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
//    while(1)
    {
        printf("Enter message : ");
//        scanf("%s" , message);
		for(i = 0; i < 6000; i++)
		{
			message[i] = 'E';
		}
         
        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
//         sleep(2);
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
//            break;
        }
         
        puts("Server reply :");
//        puts(server_reply);
//		scanf("%s", tt);
    }
     
    close(sock);
    return 0;
}

