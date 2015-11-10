#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdint.h>
#include <errno.h>

#include "debug.h"

#define MAXPENDING 5    /* Max connection requests */
#define BUFFSIZE 256

const char *test_str = "test inter ttt";

 
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

void send_data(int sock) {
	write(sock, test_str, strlen(test_str));
}

const char *server_ip = "192.168.254.128";


int main(int argc, char *argv[]) {
	int test_sock;
	struct sockaddr_in test_server;
	uint16_t port;

	if (argc != 2) {
		fprintf(stderr, "USAGE: %s <port>\n", argv[0]);
		exit(1);
	}

	port = atoi(argv[1]);
	printf("port %d\n", port);
	memset(&test_server, 0, sizeof(test_server));
	test_server.sin_family = AF_INET;
	test_server.sin_port = htons(port);
	test_server.sin_addr.s_addr = inet_addr(server_ip);


	/* Create the TCP socket */
	if ((test_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("Failed to create socket");
	}
 

	if ( connect(test_sock, (struct sockaddr*)&test_server, sizeof(test_server)) < 0) {
		printf("Failed to connect\n");
		perror("Client-connect() error");

		close(test_sock);

		exit(-1);
	}


	send_data(test_sock);

	close(test_sock);
}






