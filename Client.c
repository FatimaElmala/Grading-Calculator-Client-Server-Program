/*-------------------------------------------------------------------------------------------------------------------------------
		**	Name:Fatima Tareq Elmalla
		**	ID:192551

-------------------------------------------------------------------------------------------------------------------------------*/




/*
filename server_ipaddress portno

argv[0] --> filename 
argv[1] --> server_ipaddress 
argv[2] --> portno 

*/


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netdb.h>

// defining error function
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	//declaring the needed varibales for the connection 
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server; 
	char buffer[255]; 

	if(argc < 3 )
	{
		fprintf(stderr, "Usage %s hostname port \n", argv[0]);
		exit(1);
	}
	portno = atoi(argv[2]);
	
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("error opening socket.");
	}
	else
		printf("connection successful\n");

	server= gethostbyname(argv[1]);
	if(server == NULL)
	{
		fprintf(stderr, "Error! No such host");
	}
	
	bzero((char *)&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family=AF_INET;

	// copying data from *server to struct serv_addr
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	
	serv_addr.sin_port = htons(portno);


	//connecting to the server 
	if (connect (sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	      error("connection error! \n");    

	
	//declaring the varibales needed for calculation 
   	int num[5], result, choice; 
	char answer; 


	while(1)
	{


		//loop to send grades to the server
		for(int i=0; i<5; i++)
		{
			bzero(buffer, 255);  //reading server string
			n=read(sockfd, buffer, 255);
			if(n<0) error("Error reading from socket");
			printf("server- %s\n",buffer);  
			scanf("%d", &num[i]);      // Entering grade 1       
		 	write(sockfd, &num[i], sizeof(int));//Sending grade 1 to the server 
		}

		//Reading final grade from the server
		read(sockfd, &answer,1);
		printf("Server- Your grade is: %c\n", answer);


		bzero(buffer, 255);  //reading server string
		n=read(sockfd, buffer, 255);
		if(n<0) error("Error reading from socket");
		printf("server- %s\n",buffer);  
		scanf("%d", &choice);      // Entering Choice       
		write(sockfd, &choice, sizeof(int));//Sending choice to the server 

		if(choice==2)
			break;
	}

	
	printf("You have selected to Exit\n");
	close(sockfd);
	return 0;

}









     

