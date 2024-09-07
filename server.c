// Alexander Alvarez - CNT4704 - Homework 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <limits.h>


void error(const char *message)
{
    perror(message);
    exit(1);
}

int main(int argc, char *argv[])
{
     float sockfd, newsockfd,portnumber = 9898,num1,num2,ans,length = 0;
     float rtn = INT_MAX;
     int i,j,opcode,breakpoint;
     int acceptable_ops[4] = {43,45,42,47};
     socklen_t client_length;
     char buffer[1024];
     char operation[1024];
     char numbers1[100];
     char numbers2[100];
     char opscode;

     struct sockaddr_in serv_addr, cli_addr;

     int n, end_flag, er_flag = 0;

    // The following creates a stream socket in the Internet domain
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("Error: opening socket");

    // Initializing the C Socket structure: 
     memset((char *) &serv_addr,0, sizeof(serv_addr)); 

     serv_addr.sin_family = AF_INET;

     serv_addr.sin_addr.s_addr = INADDR_ANY;

     serv_addr.sin_port = htons(portnumber);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
         error("Error: on binding");
         exit(1);
    }
           
    //5 sockets is the max size permitted by most systems.
     listen(sockfd,5);

     client_length= sizeof(cli_addr);

     // Paramaters: specified socket created with socket(), pointer to sockaddr stuct, length of sockaddr
     newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr,&client_length);

     if (newsockfd < 0) // -1 value returned if not successful
          error("Error on accept");

 	printf("\nConnected by client on 127.0.0.1 port 9898");
   while(1)
   {
    
   	er_flag = 0;
     recv(newsockfd, operation,1024,0); // Read the operation given
     printf("\nReceived question: %s\n",operation);

     length  = strlen(operation);


     for (i = 0; i < length; i++)
     {
     	 // Parse number up to operand
        while(isdigit(operation[i]))
        {
            numbers1[i] = operation[i];
            i++;
        }

        if(isalpha(operation[i]))
        {
        	er_flag = 1;
            send(newsockfd , &rtn , sizeof(float),0);
        }

        num1= atoi(numbers1);
    
    	// Marks the point at which the operand was found to later continue parsing
        breakpoint = i+1;
        opscode = operation[i];
      
        // Checks to see which operation is being used. 
        if(opscode == 43)
        	opcode = 1;
        else if(opscode == 45)
        	opcode = 2;
        else if(opscode == 42)
        	opcode = 3;
        else if(opscode == 47)
        	opcode = 4;
       

        break;
     }
 
 		int k =0;
 		// Parsing the rest of the string, starting from the breaking point
 		for (i = breakpoint; i < length; i++)
     {
     
        while (isdigit(operation[i]))
        {
            numbers2[k] = operation[i];
            i++;
            k++;
        }
        // alphabetic characters denote an errornous input
        if(isalpha(operation[i]))
        {
        	er_flag = 1;
            send(newsockfd , &rtn , sizeof(float),0);
        }

        num2= atoi(numbers2);

         break;
      }

    switch(opcode)
    {
        case 1:
        if (er_flag ==0)
        {
	        ans = num1+num2;
	        printf(";send back answer %.2f\n",ans);
        }
        break;

        case 2:
        if(er_flag == 0)
        {
	        ans = num1-num2;
	        printf(";send back answer %.2f\n",ans);
        }
        break;

        case 3: 
        if(er_flag == 0)
        {
	        ans = num1*num2;
	        printf(";send back answer %.2f\n",ans);
    	}
        break;

        case 4:
        if(er_flag == 0)
        {
		ans = num1/num2;
		printf(";send back answer %.2f\n",ans);
   	 }
        break;

    }


    if(er_flag == 0)
    {
   		 printf("Sending answer:%.2f...\n",ans);
    	send(newsockfd , &ans , sizeof(float),0);
	}

 }
      close(newsockfd);
      close(sockfd);
      return 0; 
}


