// Sample hello_server.c file

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_LENGTH 1500
#define PORT 31415

int main(void){
	
	int  				fd, conn_fd;
	ssize_t				rlen;
	struct sockaddr_in 	addr, conn_addr;
	socklen_t 			conn_addr_len;
	char 				buffer[BUFFER_LENGTH];
	int 				flags = 0;

	// Create a TCP (SOCK_STREAM) over IP scoket
	fd = socket (AF_INET, SOCK_STREAM, 0);
	if(fd == -1){
		perror("Unable to create socket.");
		return 1;
	}

	// Attempt to bind to port 31415
	addr.sin_family 		= AF_INET;
	addr.sin_port  			= htons(PORT);
	addr.sin_addr.s_addr 	= INADDR_ANY;

	if(bind(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
		perror("Unable to bind to port 31415");
		return 2;
	}

	// Listen for incoming connections
	if(listen(fd, 1) == -1){
		perror("Unable to listen for connections...");
		return 3;
	}

	// Accept the first available connection
	conn_addr_len = sizeof(struct sockaddr);
	if((conn_fd = accept(fd, (struct sockaddr *) &conn_addr, &conn_addr_len)) == -1){
		perror("Unable to accept the connection!");
		return 4;
	}

	// Retrieve the data in the packet
	while((rlen = recv(conn_fd, buf, BUFFER_LENGTH, flags)) > 0){
		int i;
		for(i = 0; i < rlen; i++){
			printf("%c", buf[i]);
		}
		printf("\n");
	}

	// Close the connection and the socket
	close(conn_fd);
	close(fd);

	return 0;
}