#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdint.h>

#include "debug.h"

#define MAXPENDING 5    /* Max connection requests */
#define BUFFSIZE 256

 
void receive_data(int sock) {
	char buffer[BUFFSIZE];
	int received = -1;
	struct ofp_header *of_hdr;

	if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
		printf("receive failed %d\n", received);
		close(sock);
		return;
	}
	while (received > 0) {
		dump_packet(buffer, received);
		dump_msg(buffer, received);
		if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
			printf("receive failed %d\n", received);
			break;
		}
	}
	close(sock);
}


int main(int argc, char *argv[]) {
	int serversock, clientsock;
	struct sockaddr_in ovsserver, echoclient;

	if (argc != 2) {
		fprintf(stderr, "USAGE: server <port>\n");
		exit(1);
	}
	/* Create the TCP socket */
	if ((serversock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("Failed to create socket");
	}
	/* Construct the server sockaddr_in structure */
	memset(&ovsserver, 0, sizeof(ovsserver));       /* Clear struct */
	ovsserver.sin_family = AF_INET;                  /* Internet/IP */
	ovsserver.sin_addr.s_addr = htonl(INADDR_ANY);   /* Incoming addr */
	ovsserver.sin_port = htons(atoi(argv[1]));       /* server port */



 
	/* Bind the server socket */
	if (bind(serversock, (struct sockaddr *) &ovsserver, sizeof(ovsserver)) < 0) {
		printf("Bind failed\n");
	}

	/* Listen on the server socket */
	if (listen(serversock, MAXPENDING) < 0) {
            printf("Failed to listen on server socket");
	}

	/* Run until cancelled */
	while (1) {
		unsigned int clientlen = sizeof(echoclient);
		/* Wait for client connection */
		if ((clientsock =
			accept(serversock, (struct sockaddr *) &echoclient, &clientlen)) < 0) {
			printf("Failed to accept client connection");
		}
		receive_data(clientsock);
	}
}






