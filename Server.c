/*-------------------------------------------------------------------------------------------------------------------------------
		**	Name:Fatima Tareq Elmalla
		**	ID:192551

-------------------------------------------------------------------------------------------------------------------------------*/


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h> 


// defining error function
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

// Driver function 
int main(int argc, char *argv[])
{
	//checking if the port number is valid or not 
	if(argc < 2 )
	{
		fprintf(stderr, "Port No. not provided. program terminated");
		exit(1);
	}
	
	//declaring the needed varibales for the connection 
	int sockfd, newsockfd, portno, n; 
	//declaring the buffer of type char that will contain the message 
	char buffer[255]; 


	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen; 

	// socket create and verification 
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("error opening socket.");
	}

	bzero( (char *)&serv_addr, sizeof(serv_addr)); //clearing data in serv_addr
	portno = atoi(argv[1]);
	// assign IP, PORT 
   	serv_addr.sin_family = AF_INET; 
    	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    	serv_addr.sin_port = htons(portno);

	// Binding newly created socket to given IP and verification 
    	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        	error("socket bind failed...\n"); 
        	
    	} 
    	else
        	printf("Socket successfully binded..\n");


	// Now server is ready to listen and verification 
    	if ((listen(sockfd, 5)) != 0) { //5 is the max. number of clients that can connect to the server 
        	error("Listen failed...\n"); 
    	} 
    	else
        	printf("Server listening..\n"); 
	clilen = sizeof(cli_addr);
 
	
	//accepting the connection
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen); 
	if (newsockfd < 0) { 
        	error("server acccept failed...\n"); 
        	
   	 } 
   	 else
        	printf("server acccept the client...\n"); 


	

	while(1)
	{
		// declaring the variables needed for the claculation process
		int num[5], result=0, choice; 
		char answer;
		char msg[17]="Enter Grade no. "; 



		//loop for asking and reading the grades from the Client 
		for(int i=0; i<5; i++)
		{
			msg[16]= (i+1)+ '0';
			n=write(newsockfd, msg,17); //asking for grades 
			if (n<0) error("Error writing to socket");
		
			read(newsockfd, &num[i], sizeof(int)); // reading grades 
			printf("Client- Grade %d is: %d\n",i+1,num[i]); // printing grades

		}


		// calculating the average grade
		for(int i=0; i<5; i++)
		{
			result+=num[i];
		}
		result/=5;

	

		//specifing the grade based on the average result 	
		if(result>=70)
		{
			answer='A';
		}	
		else if(result>=60 && result<=69 )
		{
			answer='B';
		}		
		else if(result>=50 && result<=59 )
		{
			answer='C';
		}		
		else if(result>=40 && result<=49 )
		{
			answer='D';
		}
		else
		{
			answer='F';
		}

		

		printf("Result:%i\n",result);
		//writing the final grade 
		write(newsockfd, &answer,1);
		n= write(newsockfd, "Enter your choice: \n1 for calculate\n2 for Exit ", strlen("Enter your choice: \n1 for calculate\n 2 for Exit "));//Asking for Choice
		if (n<0) error("Error writing to socket"); 
		read(newsockfd, &choice, sizeof(int));  	// Reading choice
		printf("Client - Choice is :%d\n ",choice);
		
		//breaking from the loop if the client chooses to exit 
		if(choice==2)
		break;
	
	
	}


	//closing the connection 
	close(newsockfd);
	close(sockfd);
	return 0;
 }
  









