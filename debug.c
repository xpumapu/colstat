#include <string.h>
#include <stdio.h>
#include "debug.h"




void dump_packet(char *ptr, int bytes) {
	int i;

	printf("\n");
	for (i = 0; i < bytes; i++) {
		printf("0x%x ", ptr[i]);
	}
	printf("\n");
}

void dump_msg(char *ptr, int bytes) {
	char tmp[bytes + 1];
	memcpy(tmp, ptr, bytes);
	tmp[bytes + 1] = '\0';
	printf("msg: %s\n", tmp);
}





