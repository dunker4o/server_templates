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

int main(void) {
	int 				fd;
	char 				buffer[MAXLINE];
	char 				*hello = "Hello from the other side of the internet!";
	struct sockaddr_in 	server_addr;

	// Create the socket
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("Unable to create the UDP socket.");
		return 1;
	}

	//Fillout the server information
	server_addr.sin_family 		= AF_INET;
	server_addr.sin_port 		= htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY; 

	// Send data to the server
	sendto(fd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &server_addr, sizeof(server_addr));
	printf("Greeting has been sent :)\n");

	// Close the socket
	close(fd);
	return 0;
}