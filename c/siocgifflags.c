#include <stdlib.h>
#include <stdio.h>
#include <string.h>     
#include <sys/ioctl.h>  /* ioctl()  */
#include <sys/socket.h> /* socket() */
#include <arpa/inet.h>  
#include <unistd.h>     /* close()  */
#include <linux/if.h>   /* struct ifreq */

int main(int argc, char* argv[])
{
	/* this socket doesn't really matter, we just need a descriptor 
	 * to perform the ioctl on */
	int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct ifreq ethreq;

	memset(&ethreq, 0, sizeof(ethreq));

	/* set the name of the interface we wish to check */
	strncpy(ethreq.ifr_name, "eth0", IFNAMSIZ);
	/* grab flags associated with this interface */
	ioctl(fd, SIOCGIFFLAGS, &ethreq);
	if (ethreq.ifr_flags & IFF_PROMISC) {
		printf("%s is in promiscuous mode\n",
				ethreq.ifr_name);
	} else {
		printf("%s is NOT in promiscuous mode\n",
				ethreq.ifr_name);
	}

	close(fd);

	return 0;
}
