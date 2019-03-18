// Alexander Alvarez - CNT4704 - Homework 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctype.h>
#include <limits.h>

void error(const char *message)
{
    perror(message);
    exit(1);
}

int main(int argc, char *argv[])
{
    float sockfd, portno = 9898, n, end_flag, num1,num2,ans,choice, nBytes;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[1024];
    char operation[1024];
    char null_mess[5];

    strcpy(null_mess,"null");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("Error opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) 
    {
        fprintf(stderr,"Error, no such host\n");
        exit(0);
    }
    memset((char *) &serv_addr,0,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("Error: connecting");
  

    printf("\nConnected with server on 127.0.0.1 port 9898");
    
    while (end_flag != 0)
    {
      S:  memset(operation,0,1024);


        printf("\nPlease enter mathematical calculation: ");
        fgets(operation,1024,stdin);
        printf("You entered: %s\n",operation);

        int o;
        o = strcmp("0/0\n",operation);

        if(o == 0 )
        {
            printf("User inputs ends; end the client program.\n");
            end_flag == 0;
            nBytes = strlen(null_mess)+1;

            send(sockfd,null_mess,nBytes,0); 

            goto Q;
        }

        nBytes = strlen(operation)+1;

        send(sockfd,operation,nBytes,0);      // Send Operation to Server
    
        recv(sockfd , &ans , sizeof(float),0);				//Read Answer from Server

        if (ans == INT_MAX) // if sent to int max, the input was errornous
        {
            printf("“Invalid question or space used between characters! Please restart and enter the math question again.”\n");
            goto Q;
        }

        printf("Answer from server:%.2f\n",ans);	//Get Answer from server
	     
    }
    
    Q: close(sockfd);
    return 0;
}


