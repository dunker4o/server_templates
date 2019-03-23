//Sample UDP Client

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 1500
#define PORT 31415
#define MAXINPUT 12


int main(int argc, char* argv[]) {
	int 				fd;
	char 				buffer[MAXLINE];
	char 				*hello = "Hello from the other side of the internet!\n";
	struct sockaddr_in 	server_addr;
	char 				str[MAXINPUT]; //Array for reading stdin input
	char 				*destination;

	if(argc==2){
		destination = argv[1];
	} else{
		destination = "127.0.0.1";
	}

	// Create the socket
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("Unable to create the UDP socket.");
		return 1;
	}

	//Fillout the server information
	server_addr.sin_family 		= AF_INET;
	server_addr.sin_port 		= htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.9"); 

	// Send data to the server
	while(fgets(str, MAXINPUT, stdin) != NULL){
		sendto(fd, str, strlen(str), MSG_CONFIRM, (const struct sockaddr *) &server_addr, sizeof(server_addr));
	}
	
	printf("Greeting has been sent :)\n");

	// Close the socket
	close(fd);
	return 0;
}