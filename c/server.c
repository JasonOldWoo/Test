#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>

#define SERVER_PORT 8000
#define CLIENT_PORT 9000
#define MAXLINE		1500
#define GROUP		"239.0.0.2"

int main(int argc, char* argv[])
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 服务器监听本机所有网卡 8000 端口
    struct sockaddr_in srvaddr;
    memset(&srvaddr, 0, sizeof(srvaddr));
    srvaddr.sin_family		= AF_INET;
    srvaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
    srvaddr.sin_port		= htons(SERVER_PORT);
    bind(sock, (struct sockaddr*)&srvaddr, sizeof(srvaddr));

    // 设置组播地址
    struct ip_mreqn group;
    inet_pton(AF_INET, GROUP, &group.imr_multiaddr);	// 组
    inet_pton(AF_INET, "0.0.0.0", &group.imr_address);	// ip
    group.imr_ifindex = if_nametoindex("eth0");			// 网卡索引号
    // 设置发送数据包是组播方式发送
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));

    // 构建发送目标结构体
    struct sockaddr_in cntaddr;
    memset(&cntaddr, 0, sizeof(cntaddr));
    cntaddr.sin_family		= AF_INET;
    cntaddr.sin_port		= htons(CLIENT_PORT);		// 目标端口
    inet_pton(AF_INET, GROUP, &cntaddr.sin_addr.s_addr);// 目标的组地址
    
    char buf[MAXLINE];
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        sendto(sock, buf, strlen(buf), 0, 
                (struct sockaddr*)&cntaddr, sizeof(cntaddr));
        sleep(1);
    }
    
    close(sock);
    return 0;
}
