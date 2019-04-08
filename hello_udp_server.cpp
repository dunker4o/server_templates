// Sample UDP server file

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_LENGTH 1500
#define PORT 31415

int main(void){
	
	int  					fd;
	ssize_t					rlen;
	struct sockaddr_in 		addr, conn_addr;
	socklen_t 				conn_addr_len;
	char 					buffer[BUFFER_LENGTH];
	int 					flags = 0;
	// Needed for UDP connection as per https:linux.die.net/man/3/getaddrinfo
	struct sockaddr_storage client_addr;
	socklen_t 				client_addr_len;

	//Network IP discovery
	int broadcast = 1;

	// Create a UDP (SOCK_DGRAM) over IP scoket
	fd = socket (AF_INET, SOCK_DGRAM, 0);
	if(fd == -1){
		perror("Unable to create socket.");
		return 1;
	}


	if(setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast)) < 0){
        perror("Error in setting Broadcast option");
        close(fd);
        return 3;
    }

	// Attempt to bind to port 31415
	addr.sin_family 		= fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
		perror("Unable to bind to port 31415");
		return 2;
	}

	
	// Retrieve the data in the packet
	client_addr_len = sizeof(struct sockaddr_storage);
	while((rlen = recvfrom(fd, buffer, BUFFER_LENGTH, flags, (struct sockaddr *) &client_addr, &client_addr_len)) > 0){
		int i;
		for(i = 0; i < rlen; i++){
			printf("%c", buffer[i]);
		}
	}

	// Close the socket
	close(fd);

	return 0;
}