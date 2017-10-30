#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/route.h>
#include <arpa/inet.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <errno.h>

#pragma GCC diagnostic ignored "-Wstrict-aliasing"

#define NET_NL_BUFSIZE 8192
struct NetRouteInfo_t
{
	char    szIfName[IF_NAMESIZE];
	u_int   unGateway;
	u_int   unSrcAddr;
	u_int   unDstAddr;
};

static int
NLI_ReadNlSock(int nSock, char* pBuf, int nSeqNum, int nPid)
{
	struct nlmsghdr* pNlHdr = NULL;
	int nReadLen = 0, nMsgLen = 0;
	while (1) {
		if ((nReadLen = recv(nSock, pBuf, NET_NL_BUFSIZE - nMsgLen, 0)) < 0) {
			printf("%s ****recv error!\n", __FUNCTION__);
			return -1;
		}
		pNlHdr = (struct nlmsghdr*) pBuf;
		if ((NLMSG_OK(pNlHdr, (unsigned int) nReadLen) == 0)
			|| (pNlHdr->nlmsg_type == NLMSG_ERROR)) {
			printf("%s ****nlmsg error!\n", __FUNCTION__);
			return -1;
		}
		if (pNlHdr->nlmsg_type == NLMSG_DONE) {
			break ;
		} else {
			pBuf += nReadLen;
			nMsgLen += nReadLen;
		}
		if (pNlHdr->nlmsg_flags & NLM_F_MULTI) {
			break ;
		}
		if (pNlHdr->nlmsg_seq != (unsigned int) nSeqNum
			|| (pNlHdr->nlmsg_pid != (unsigned int) nPid)) {
			break ;
		}
	}
	return nMsgLen;
}

static int
NLI_ParseRoute(struct nlmsghdr* pNlHdr, struct NetRouteInfo_t* pRtInfo, char* pDefaultGateway)
{
	int nRtLen = 0;
	struct in_addr tDst;
	struct in_addr tGate;
	struct rtmsg* pRtMsg = NULL;
	struct rtattr* pRtAttr = NULL;
	pRtMsg = (struct rtmsg*) NLMSG_DATA(pNlHdr);
	if ((pRtMsg->rtm_family != AF_INET)
		|| (pRtMsg->rtm_table != RT_TABLE_MAIN)) {
		//printf("%s ****rtm family: %d, rtm_table: %d error!\n", __FUNCTION__, pRtMsg->rtm_family, pRtMsg->rtm_table);
		return -1;
	}
	pRtAttr = (struct rtattr*) RTM_RTA(pRtMsg);
	nRtLen = RTM_PAYLOAD(pNlHdr);
	for (; RTA_OK(pRtAttr, nRtLen); pRtAttr = RTA_NEXT(pRtAttr, nRtLen)) {
		switch (pRtAttr->rta_type) {
		case RTA_OIF:
			if_indextoname(*(int*) RTA_DATA(pRtAttr), pRtInfo->szIfName);
			break ;
		case RTA_GATEWAY:
			pRtInfo->unGateway = *(u_int*) RTA_DATA(pRtAttr);
			break ;
		case RTA_PREFSRC:
			pRtInfo->unSrcAddr = *(u_int*) RTA_DATA(pRtAttr);
			break ;
		case RTA_DST:
			pRtInfo->unDstAddr = *(u_int*) RTA_DATA(pRtAttr);
			break ;
		};
	}
	tDst.s_addr = pRtInfo->unDstAddr;
	if (strstr((char*)inet_ntoa(tDst), "0.0.0.0")) {
		tGate.s_addr = pRtInfo->unGateway;
		strncpy(pDefaultGateway, (char*) inet_ntoa(tGate), 32);
	}

	return 0;
}

/*!
 * @brief get default gateway by plNetDev
 */
int
NL_GetDefaultGateway(const char* lpNetDev, char* pDefaultGateway)
{
	static char szGatewayTmp[16] = {0};
	static char szMsgBuf[NET_NL_BUFSIZE] = {0};
	static struct NetRouteInfo_t tRi;
	int nRet = -1;
	struct nlmsghdr* pNlMsg = NULL;
	struct rtmsg* pRtMsg = NULL;
	struct NetRouteInfo_t* pRtInfo = &tRi;
	int nLen = 0, nMsgSeq = 0;
	int nSock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		goto END;
	}
	pNlMsg = (struct nlmsghdr*) szMsgBuf;
	pRtMsg = (struct rtmsg*) NLMSG_DATA(pNlMsg);
	pNlMsg->nlmsg_len = NLMSG_LENGTH(sizeof (struct rtmsg));
	pNlMsg->nlmsg_type = RTM_GETROUTE;
	pNlMsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST;
	pNlMsg->nlmsg_seq = nMsgSeq++;
	pNlMsg->nlmsg_pid = getpid();
	// send nlsock
	if (send(nSock, pNlMsg, pNlMsg->nlmsg_len, 0) < 0) {
		printf("%s ****send nlsock error!\n", __FUNCTION__);
		goto END;
	}
	// recv nlsock
	if ((nLen = NLI_ReadNlSock(nSock, szMsgBuf, nMsgSeq, getpid())) < 0) {
		printf("%s ****recv nlsock error!\n", __FUNCTION__);
		goto END;
	}
	if (pRtInfo != NULL) {
		for (; NLMSG_OK(pNlMsg, (unsigned int) nLen); pNlMsg = NLMSG_NEXT(pNlMsg, nLen))
		{
			memset(szGatewayTmp, 0, sizeof (szGatewayTmp));
			memset(pRtInfo, 0, sizeof (struct NetRouteInfo_t));
			if (0 == NLI_ParseRoute(pNlMsg, pRtInfo, szGatewayTmp)) {
				if (strcmp(pRtInfo->szIfName, lpNetDev) == 0
					&& strcmp(szGatewayTmp, "0.0.0.0") != 0
					&& strlen(szGatewayTmp) > 0) {
					strncpy(pDefaultGateway, szGatewayTmp, 32);
					nRet = 0;
				}
			}
		}
	}

END:
	if (nSock > 0) {
		close(nSock);
		nSock = -1;
	}
	return nRet;
}

/*
 * @brief set default gateway
 */
int
NL_SetDefaultGateway(const char* lpNetDev, const char* lpIpAddr, const char* lpGateway, const char* lpNetmask)
{
    int nRet = -1;
    int nSock;
    struct rtentry tRtEntry;
    struct sockaddr_in* pAddr;
    nSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (nSock < 0) {
        printf("%s ****socket error\n", __FUNCTION__);
        goto END;
    }
    memset(&tRtEntry, 0x0, sizeof (struct rtentry));
    pAddr = (struct sockaddr_in*) &tRtEntry.rt_dst;
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = 0;
    pAddr->sin_addr.s_addr = INADDR_ANY;
    tRtEntry.rt_flags = RTF_UP | RTF_MODIFIED | RTF_GATEWAY;
    tRtEntry.rt_dev = (char*) lpNetDev;
    // delete old default gateway
    if (ioctl(nSock, SIOCDELRT, &tRtEntry) < 0) {
        printf("%s ****ioctl SIOCDELRT error!\n", __FUNCTION__);
        printf("%s ****errmsg: %s\n", __FUNCTION__, strerror(errno));
        //goto END;
    }
    memset(&tRtEntry, 0x0, sizeof (struct rtentry));
    tRtEntry.rt_flags = RTF_UP | RTF_MODIFIED;
    tRtEntry.rt_dev = (char*) lpNetDev;
    pAddr = (struct sockaddr_in*) &tRtEntry.rt_genmask;
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = 0;
    pAddr->sin_addr.s_addr = inet_addr(lpNetmask);
    pAddr = (struct sockaddr_in*) &tRtEntry.rt_dst;
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = 0;
    pAddr->sin_addr.s_addr = inet_addr(lpIpAddr) & inet_addr(lpNetmask);
    if (ioctl(nSock, SIOCDELRT, &tRtEntry) < 0) {
        printf("%s ****ioctl SIOCDELRT 2 error!\n", __FUNCTION__);
        //goto END;
    }
    memset(&tRtEntry, 0x0, sizeof (struct rtentry));
    tRtEntry.rt_flags = RTF_UP | RTF_MODIFIED;
    tRtEntry.rt_dev = (char*) lpNetDev;
    pAddr = (struct sockaddr_in*) &tRtEntry.rt_genmask;
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = 0;
    pAddr->sin_addr.s_addr = inet_addr(lpNetmask);
    pAddr = (struct sockaddr_in*) &tRtEntry.rt_dst;
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = 0;
    pAddr->sin_addr.s_addr = inet_addr(lpIpAddr) & inet_addr(lpNetmask);
    tRtEntry.rt_metric = 0;
    // accept this route
    if (ioctl(nSock, SIOCADDRT, &tRtEntry) < 0) {
        printf("%s ****ioctl SIOCADDRT error!\n", __FUNCTION__);
        goto END;
    }
    memset(&tRtEntry, 0x0, sizeof (struct rtentry));
    tRtEntry.rt_flags = RTF_UP | RTF_MODIFIED;
    tRtEntry.rt_dev = (char*) lpNetDev;
    tRtEntry.rt_metric = 0;
    // gateway
    pAddr = (struct sockaddr_in*) &tRtEntry.rt_gateway;
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = 0;
    pAddr->sin_addr.s_addr = inet_addr(lpGateway);
    pAddr = (struct sockaddr_in*) &tRtEntry.rt_dst;
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = 0;
    pAddr->sin_addr.s_addr = INADDR_ANY;
    tRtEntry.rt_flags |= RTF_GATEWAY;
    // accept this route
    if (ioctl(nSock, SIOCADDRT, &tRtEntry) < 0) {
        printf("%s ****ioctl SIOCADDRT 2 error!\n", __FUNCTION__);
        goto END;
    }
    nRet = 0;

END:
    if (nSock > 0) {
        close(nSock);
        nSock = -1;
    }
    return nRet;
}

/*!
 * @brief add route
 */
int NL_AddRoute(const char* lpNetDev, const char* lpRoute, const char* lpNetmask)
{
    if (!lpRoute) {
        printf("%s ****error!\n", __FUNCTION__);
        return -1;
    }
    int nRet = -1;
    int nSock;
    struct sockaddr_in* pAddr;
    struct rtentry tRtEntry;

    nSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (nSock < 0)
    {
        printf("%s ****socket error!\n", __FUNCTION__);
        goto END;
    }

    memset(&tRtEntry, 0, sizeof(struct rtentry));
    if (lpRoute) {
        pAddr = (struct sockaddr_in*) &tRtEntry.rt_dst;
        pAddr->sin_family = AF_INET;
        pAddr->sin_port = 0;
        pAddr->sin_addr.s_addr = inet_addr(lpRoute);
    }
    if (lpNetmask) {
        pAddr = (struct sockaddr_in*) &tRtEntry.rt_genmask;
        pAddr->sin_family = AF_INET;
        pAddr->sin_port = 0;
        pAddr->sin_addr.s_addr = inet_addr(lpNetmask);
    }
    tRtEntry.rt_dev = (char*) lpNetDev;
    tRtEntry.rt_flags = RTF_UP;
    // add route
    if (ioctl(nSock, SIOCADDRT, &tRtEntry) < 0)
    {
        printf("%s ****ioctl SIOCADDRT error!\n", __FUNCTION__);
        printf("%s ****errmsg: %s\n", __FUNCTION__, strerror(errno));
        goto END;
    }
    nRet = 0;

END:
    if (nSock < 0) {
        close(nSock);
        nSock = -1;
    }
    return nRet;
}

/*!
 * @brief del route
 */
int NL_DelRoute(const char* lpNetDev, const char* lpRoute, const char* lpNetmask)
{
    if (!lpRoute) {
        printf("%s ****error!\n", __FUNCTION__);
        return -1;
    }
    int nRet = -1;
    int nSock;
    struct sockaddr_in* pAddr;
    struct rtentry tRtEntry;

    nSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (nSock < 0)
    {
        printf("%s ****socket error!\n", __FUNCTION__);
        goto END;
    }

    memset(&tRtEntry, 0, sizeof(struct rtentry));
    if (lpRoute) {
        pAddr = (struct sockaddr_in*) &tRtEntry.rt_dst;
        pAddr->sin_family = AF_INET;
        pAddr->sin_port = 0;
        pAddr->sin_addr.s_addr = inet_addr(lpRoute);
    }
    if (lpNetmask) {
        pAddr = (struct sockaddr_in*) &tRtEntry.rt_genmask;
        pAddr->sin_family = AF_INET;
        pAddr->sin_port = 0;
        pAddr->sin_addr.s_addr = inet_addr(lpNetmask);
    }
    tRtEntry.rt_dev = (char*) lpNetDev;
    tRtEntry.rt_flags = RTF_UP;
    // del route
    if (ioctl(nSock, SIOCDELRT, &tRtEntry) < 0)
    {
        printf("%s ****ioctl SIOCDELRT error!\n", __FUNCTION__);
        printf("%s ****error message: %s\n", __FUNCTION__, strerror(errno));
        goto END;
    }
    nRet = 0;

END:
    if (nSock < 0) {
        close(nSock);
        nSock = -1;
    }
    return nRet;
}

/*!
 * @brief get ip address, subnet mask and mac address by lpNetDev
 */
int
NL_GetLocalNetInfo(const char* lpNetDev, char* pIpAddr, char* pNetmask, char* pMacAddr)
{
	int nRet = 0;
	struct ifreq tReq;
	struct sockaddr_in* pHost = NULL;
	int nSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		return -1;
	}

	bzero(&tReq, sizeof (struct ifreq));
	strncpy(tReq.ifr_name, lpNetDev, IFNAMSIZ);
	if (ioctl(nSock, SIOCGIFADDR, &tReq) >= 0) {
		pHost = (struct sockaddr_in*) &tReq.ifr_addr;
		strncpy(pIpAddr, inet_ntoa(pHost->sin_addr), 16);
	} else {
		printf("%s ****get ip addr error!\n", __FUNCTION__);
		nRet = -1;
	}

	bzero(&tReq, sizeof (struct ifreq));
	strncpy(tReq.ifr_name, lpNetDev, IFNAMSIZ);
	if (ioctl(nSock, SIOCGIFNETMASK, &tReq) >= 0) {
		pHost = (struct sockaddr_in*) &tReq.ifr_addr;
		strncpy(pNetmask, inet_ntoa(pHost->sin_addr), 16);
	} else {
		printf("%s ****get netmask error!\n", __FUNCTION__);
		nRet = -1;
	}
	bzero(&tReq, sizeof (struct ifreq));
	strncpy(tReq.ifr_name, lpNetDev, IFNAMSIZ);
	if (ioctl(nSock, SIOCGIFHWADDR, &tReq) >= 0) {
		sprintf(pMacAddr, "%02x:%02x:%02x:%02x:%02x:%02x",
		(unsigned char) tReq.ifr_hwaddr.sa_data[0],
		(unsigned char) tReq.ifr_hwaddr.sa_data[1],
		(unsigned char) tReq.ifr_hwaddr.sa_data[2],
		(unsigned char) tReq.ifr_hwaddr.sa_data[3],
		(unsigned char) tReq.ifr_hwaddr.sa_data[4],
		(unsigned char) tReq.ifr_hwaddr.sa_data[5]);
	} else {
		printf("%s ****get hwaddr error!\n", __FUNCTION__);
		nRet = -1;
	}

	if (nSock > 0) {
		close(nSock);
		nSock = -1;
	}

	return nRet;
}
/*!
 * @brief set ip address and subnet mask by lpNetDev
 */
int NL_SetLocalNetInfo(const char* lpNetDev, const char* lpIpAddr, const char* lpNetmask)
{
	int nRet = -1;
	struct ifreq tReq;
	struct sockaddr_in* pHost = NULL;
	int nSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		goto END;
	}
	bzero(&tReq, sizeof (struct ifreq));
	strncpy(tReq.ifr_name, lpNetDev, IFNAMSIZ);
	pHost = (struct sockaddr_in*) &tReq.ifr_addr;
	pHost->sin_family = AF_INET;
	// inet_pton returns 1 on success
	if (1 != inet_pton(AF_INET, lpIpAddr, &(pHost->sin_addr))) {
		printf("%s ****inet_pton ip addr error!\n", __FUNCTION__);
		goto END;
	}
	// set ip addr
	if (ioctl(nSock, SIOCSIFADDR, &tReq) < 0) {
        printf("%s ****ioctl SIOCSIFADDR error!\n", __FUNCTION__);
        printf("%s ****net dev: %s, ip addr: %s\n", __FUNCTION__, lpNetDev, lpIpAddr);
		goto END;
	}
	bzero(&tReq, sizeof (struct ifreq));
	strncpy(tReq.ifr_name, lpNetDev, IFNAMSIZ);
	pHost = (struct sockaddr_in*) &tReq.ifr_addr;
	pHost->sin_family = AF_INET;
	if (1 != inet_pton(AF_INET, lpNetmask, &(pHost->sin_addr))) {
		printf("%s ****inet_pton net mask error!\n", __FUNCTION__);
		goto END;
	}
	// set net mask
	if (ioctl(nSock, SIOCSIFNETMASK, &tReq) < 0) {
		printf("%s ****ioctl SIOCSIFNETMASK error!\n", __FUNCTION__);
        printf("%s ****net dev: %s, net mask: %s\n", __FUNCTION__, lpNetDev, lpNetmask);
		goto END;
	}
	nRet = 0;

END:
	if (nSock < 0) {
		close(nSock);
		nSock = -1;
	}
	return nRet;
}

/*!
 * @brief set mtu by lpNetDev
 */
int
NL_SetMtu(const char* lpNetDev, unsigned int nMtu)
{
	int nRet = -1;
	struct ifreq tReq;
	int nSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		goto END;
	}
	strncpy(tReq.ifr_name, lpNetDev, IFNAMSIZ);
	tReq.ifr_ifru.ifru_mtu = nMtu;
	// set mtu
	if (ioctl(nSock, SIOCSIFMTU, &tReq) < 0) {
		printf("%s ****ioctl SIOCSIFMTU error!\n", __FUNCTION__);
		goto END;
	}
	nRet = 0;

END:
	if (nSock != -1) {
		close(nSock);
		nSock = -1;
	}
	return nRet;
}

/*!
 * @brief set netcard down
 */
int
NL_SetIfDown(const char* lpNetDev)
{
	int nRet = -1;
	struct ifreq tReq;
	int nSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		goto END;
	}
	strncpy(tReq.ifr_name, lpNetDev, IFNAMSIZ);
	// get flag
	if (ioctl(nSock, SIOCGIFFLAGS, &tReq) < 0) {
		printf("%s ****ioctl SIOCGIFFLAGS error!\n", __FUNCTION__);
		goto END;
	}
	tReq.ifr_flags &= ~IFF_UP;
	// set flag
	if (ioctl(nSock, SIOCSIFFLAGS, &tReq) < 0) {
		printf("%s ****ioctl SIOCSIFFLAGS error!\n", __FUNCTION__);
		goto END;
	}
	nRet = 0;

END:
	if (nSock != -1) {
		close(nSock);
		nSock = -1;
	}
	return nRet;
}

/*!
 * @brief set netcard up
 */
int
NL_SetIfUp(const char* pNetDev)
{
	int nRet = -1;
	struct ifreq tReq;
	int nSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		goto END;
	}
	strncpy(tReq.ifr_name, pNetDev, IFNAMSIZ);
	// get flag
	if (ioctl(nSock, SIOCGIFFLAGS, &tReq) < 0) {
		printf("%s ****ioctl SIOCGIFFLAGS error!\n", __FUNCTION__);
		goto END;
	}
	tReq.ifr_flags |= IFF_UP;
	// set flag
	if (ioctl(nSock, SIOCSIFFLAGS, &tReq) < 0) {
		printf("%s ****ioctl SIOCSIFFLAGS error!\n", __FUNCTION__);
		goto END;
	}
	nRet = 0;

END:
	if (nSock != -1) {
		close(nSock);
		nSock = -1;
	}
	return nRet;
}

#ifdef NETCARD_NET_UNITEST
int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("Usage: %s <ip address>\n", argv[0]);
		exit(1);
	}
	char szIpAddr[255] = "";
	char szNetmask[255] = "";
	char szMacAddr[255] = "";
	NL_GetLocalNetInfo("eth0", szIpAddr, szNetmask, szMacAddr);
	printf("ipaddr: %s\nnetmask: %s\nhwaddr: %s\n", szIpAddr, szNetmask, szMacAddr);
	strncpy(szIpAddr, argv[1], 255);
	NL_SetLocalNetInfo("eth0", szIpAddr, "255.255.255.0");
	printf("set local net info!\n");
	NL_GetLocalNetInfo("eth0", szIpAddr, szNetmask, szMacAddr);
	printf("ipaddr: %s\nnetmask: %s\nhwaddr: %s\n", szIpAddr, szNetmask, szMacAddr);
	return 0;
}
#endif