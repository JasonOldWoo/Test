#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>


#define BUFSIZE 8192
struct RouteInfo_t
{
	char    szIfName[IF_NAMESIZE];
	u_int   unGateway;
	u_int   unSrcAddr;
	u_int   unDstAddr;
};

static int
NLI_ReadNlSock(int nSock, char* pBuf, int nSeqNum, int nPld)
{
	struct nlmsghdr* pNlHdr = NULL;
	int nReadLen = 0, nMsgLen = 0;
	while (1) {
		if ((nReadLen = recv(nSock, pBuf, BUFSIZE - nMsgLen, 0)) < 0) {
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
			|| (pNlHdr->nlmsg_pid != (unsigned int) nPld)) {
			break ;
		}
	}
	return nMsgLen;
}

static int
NLI_ParseRoute(struct nlmsghdr* pNlHdr, struct RouteInfo_t* pRtInfo, char* szDefaultGateway)
{
	int nRtLen = 0;
	struct in_addr tDst;
	struct in_addr tGate;
	struct rtmsg* pRtMsg = NULL;
	struct rtattr* pRtAttr = NULL;
	pRtMsg = (struct rtmsg*) NLMSG_DATA(pNlHdr);
	if ((pRtMsg->rtm_family != AF_INET)
		|| (pRtMsg->rtm_table != RT_TABLE_MAIN)) {
		printf("%s ****rtm family: %d, rtm_table: %d error!\n",
			__FUNCTION__, pRtMsg->rtm_family, pRtMsg->rtm_table);
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
		strcpy(szDefaultGateway, (char*) inet_ntoa(tGate));
	}

	return 0;
}

int
NL_GetDefaultGateway(const char* lpszEth, char* szDefaultGateway)
{
	static char szGatewayTmp[32] = {0};
	static char szMsgBuf[BUFSIZE] = {0};
	static struct RouteInfo_t tRi;
	int nRet = -1;
	struct nlmsghdr* pNlMsg = NULL;
	struct rtmsg* pRtMsg = NULL;
	struct RouteInfo_t* pRtInfo = &tRi;
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
			memset(pRtInfo, 0, sizeof (struct RouteInfo_t));
			if (0 == NLI_ParseRoute(pNlMsg, pRtInfo, szGatewayTmp)) {
				if (strcmp(pRtInfo->szIfName, lpszEth) == 0
					&& strcmp(szGatewayTmp, "0.0.0.0") != 0
					&& strlen(szGatewayTmp) > 0) {
					strcpy(szDefaultGateway, szGatewayTmp);
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



/*!
 * @brief get ip address, subnet mask and mac address
 */
int
NL_GetLocalNetInfo(const char* lpszEth, char* szIpAddr, char* szNetmask, char* szMacAddr)
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
	strcpy(tReq.ifr_name, lpszEth);
	if (ioctl(nSock, SIOCGIFADDR, &tReq) >= 0) {
		pHost = (struct sockaddr_in*) &tReq.ifr_addr;
		strcpy(szIpAddr, inet_ntoa(pHost->sin_addr));
	} else {
		printf("%s ****get ip addr error!\n", __FUNCTION__);
		nRet = -1;
	}

	bzero(&tReq, sizeof (struct ifreq));
	strcpy(tReq.ifr_name, lpszEth);
	if (ioctl(nSock, SIOCGIFNETMASK, &tReq) >= 0) {
		pHost = (struct sockaddr_in*) &tReq.ifr_addr;
		strcpy(szNetmask, inet_ntoa(pHost->sin_addr));
	} else {
		printf("%s ****get netmask error!\n", __FUNCTION__);
		nRet = -1;
	}
	bzero(&tReq, sizeof (struct ifreq));
	strcpy(tReq.ifr_name, lpszEth);
	if (ioctl(nSock, SIOCGIFHWADDR, &tReq) >= 0) {
		sprintf(szMacAddr, "%02x:%02x:%02x:%02x:%02x:%02x",
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
 * @brief set ip address and subnet mask
 */
int NL_SetLocalNetInfo(const char* lpszEth, const char* lpszIpAddr, const char* lpszNetmask)
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
	strcpy(tReq.ifr_name, lpszEth);
	pHost = (struct sockaddr_in*) &tReq.ifr_addr;
	pHost->sin_family = AF_INET;
	// inet_pton returns 1 on success
	if (1 != inet_pton(AF_INET, lpszIpAddr, &(pHost->sin_addr))) {
		printf("%s ****inet_pton ip addr error!\n", __FUNCTION__);
		goto END;
	}
	// set ip addr
	if (ioctl(nSock, SIOCSIFADDR, &tReq) < 0) {
		printf("%s ****ioctl SIOCSIFADDR error!\n", __FUNCTION__);
		goto END;
	}
	bzero(&tReq, sizeof (struct ifreq));
	strcpy(tReq.ifr_name, lpszEth);
	pHost = (struct sockaddr_in*) &tReq.ifr_addr;
	pHost->sin_family = AF_INET;
	if (1 != inet_pton(AF_INET, lpszNetmask, &(pHost->sin_addr))) {
		printf("%s ****inet_pton net mask error!\n", __FUNCTION__);
		goto END;
	}
	// set net mask
	if (ioctl(nSock, SIOCSIFNETMASK, &tReq) < 0) {
		printf("%s ****ioctl SIOCSIFNETMASK error!\n", __FUNCTION__);
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
 * @brief set netcard mtu
 */
int
NL_SetMtu(const char* lpszEth, unsigned int nMtu)
{
	int nRet = -1;
	struct ifreq tReq;
	int nSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		goto END;
	}
	strcpy(tReq.ifr_name, lpszEth);
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
NL_SetIfDown(const char* lpszEth)
{
	int nRet = -1;
	struct ifreq tReq;
	int nSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		goto END;
	}
	strcpy(tReq.ifr_name, lpszEth);
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
NL_SetIfUp(const char* lpszEth)
{
	int nRet = -1;
	struct ifreq tReq;
	int nSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (nSock < 0) {
		printf("%s ****socket error!\n", __FUNCTION__);
		goto END;
	}
	strcpy(tReq.ifr_name, lpszEth);
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
	char szDlfGw[32] = "";
	NL_GetDefaultGateway("eth0", szDlfGw);
	printf("default gateway: %s\n", szDlfGw);
	return 0;
}
