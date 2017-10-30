#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <net/if.h>
#include <arpa/inet.h>

#define SERVER_PORT 8000
#define CLIENT_PORT 9000
#define MAXLINE		4096
#define GROUP		"239.0.0.2"

int main(int argc, char* argv[])
{
    int result;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in localaddr;
    memset(&localaddr, 0, sizeof(localaddr));
    localaddr.sin_family	= AF_INET;
    localaddr.sin_port		= htons(CLIENT_PORT);
    inet_pton(AF_INET, "0.0.0.0", &localaddr.sin_addr.s_addr);
    result = bind(sock, (struct sockaddr*)&localaddr, sizeof(localaddr));
    if (-1 == result)
    {
        perror("bind");
    }

    struct ip_mreqn group;
    inet_pton(AF_INET, GROUP, &group.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &group.imr_address);
    group.imr_ifindex = if_nametoindex("eth0");

    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group));

    int ret;
    char buf[MAXLINE];
    while (1)
    {
        ret = recvfrom(sock, buf, sizeof(buf), 0, NULL, 0);
        write(STDOUT_FILENO, buf, ret);
    }
    close(sock);
    return 0;
}
