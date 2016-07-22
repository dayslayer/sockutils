#ifndef SOCKUTILS_H_INCLUDED
#define SOCKUTILS_H_INCLUDED


#include <sys/socket.h>


int tcp4_client (char *host, int port);
int tcp4_server (int port, int backlog);
int udp4_client (char *host, int port);
int udp4_server (int port, int backlog);

int send_all (int sock, const void *buf, unsigned len, int flags);


#endif // SOCKUTILS_H_INCLUDED

