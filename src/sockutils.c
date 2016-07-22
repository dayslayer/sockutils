#include "../include/sockutils.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>


int tcp4_client (char *host, int port)
{
    int sock;
    struct sockaddr_in addr;
    struct addrinfo hints, *ainfo;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0)
        return -1;

    /* connect */

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (!inet_pton(AF_INET, host, &addr.sin_addr.s_addr)) {
        /* not an IPv4 address, try DNS lookup */
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        if (getaddrinfo(host, NULL, &hints, &ainfo) != 0) {
            close(sock);
            return -1;
        }
        /* use first addrinfo in list */
        memcpy(&addr.sin_addr, &((struct sockaddr_in*) ainfo->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(ainfo);
    }

    if (connect(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        close(sock);
        return -1;
    }

    return sock;
}

int tcp4_server (int port, int backlog)
{
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0)
        return -1;

    if (bind(sock, INADDR_ANY, sizeof(struct sockaddr_in)) < 0) {
        close(sock);
        return -1;
    }

    if (listen(sock, backlog) < 0) {
        close(sock);
        return -1;
    }

    return sock;
}

int udp4_client (char *host, int port)
{
    int sock;
    struct sockaddr_in addr;
    struct addrinfo hints, *ainfo;

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock < 0)
        return -1;

    if (host != NULL) {
        /* associate socket to a specific remote endpoint */
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        if (!inet_pton(AF_INET, host, &addr.sin_addr.s_addr)) {
            /* not an IPv4 address, try DNS lookup */
            memset(&hints, 0, sizeof(struct addrinfo));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_DGRAM;
            hints.ai_protocol = IPPROTO_UDP;
            if (getaddrinfo(host, NULL, &hints, &ainfo) != 0) {
                close(sock);
                return -1;
            }
            /* use first addrinfo in list */
            memcpy(&addr.sin_addr, &((struct sockaddr_in*) ainfo->ai_addr)->sin_addr, sizeof(struct in_addr));
            freeaddrinfo(ainfo);
        }

        if (connect(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
            close(sock);
            return -1;
        }
    }

    return sock;
}

int udp4_server (int port, int backlog)
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock < 0)
        return -1;

    if (bind(sock, INADDR_ANY, sizeof(struct sockaddr_in)) < 0) {
        close(sock);
        return -1;
    }

    if (listen(sock, backlog) < 0) {
        close(sock);
        return -1;
    }

    return sock;
}

int send_all (int sock, const void *buf, unsigned len, int flags)
{
    unsigned ret;
    unsigned sent = 0;

    do { /* allow sending zero-length tcp messages */
        ret = send(sock, buf+sent, len-sent, flags);
        if (ret < 0)
            return -1;
        sent += ret;
    }
    while (sent < len);

    return sent;
}

