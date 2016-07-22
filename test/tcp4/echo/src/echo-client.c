#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../../../include/sockutils.h"


/* max length of message buffer */
#define MAXBUF 512
/* max length of each argument */
#define MAXSTR 32


int main (int argc, char **argv)
{
	int cl_sock;
	char buf[MAXBUF];
	char *host;
	int port;
	int i, arglen;
	int buflen, nsent;

	if (argc < 3) {
		printf("Usage: echo-client HOST PORT [MSG]\n");
		return -1;
	}

	host = argv[1];
	port = atoi(argv[2]);

	buf[0] = '\0';
	for (i = 3; i < argc; i++) {
		arglen = strnlen(argv[i], MAXSTR);
		if (strnlen(buf, MAXBUF) + arglen < MAXBUF) {
			strncat(buf, argv[i], arglen);
			if (i < argc-1 && strnlen(buf, MAXBUF) + 1 < MAXBUF) {
				strcat(buf, " ");
			}
		}
	}

	//printf("%s\n", buf);

	cl_sock = tcp4_client(host, port);

	if (cl_sock < 0) {
		printf("Failed to create tcp4_client: %d\n", cl_sock);
		return -2;
	}

	buflen = strnlen(buf, MAXBUF);
	nsent = send_all(cl_sock, buf, buflen, 0);

	if (nsent < 0) {
		printf("Error sending data\n");
	} else {
		printf("Sent: %d/%d\n", nsent, buflen);
	}

	shutdown(cl_sock, SHUT_RDWR);
	close(cl_sock);

	return 0;
}

