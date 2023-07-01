#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <string.h>

using namespace std;

struct sockaddr_in target, from;

int main(int argc, char *argv[]) {
    cout << "uid: " << getuid() << endl;
    cout << "eid: " << geteuid() << endl;

    // prctl(PR_CAPBSET_READ, 0x28 /* CAP_??? */);

#ifdef HAVE_LIBCAP
    cout << "LIB_CAP" << endl;
#else
    cout << "NO LIB_CAP" << endl;
#endif

    if(argc!=2) {
        printf("Usage:%s targetip\n", argv[0]);
        exit(1);
	}

	if (0 == inet_aton(argv[1], &target.sin_addr)) {
        printf("bad ip address %s\n",argv[1]);
        exit(1);
    }

    // struct icmp * icmp;
    // char sendbuff[8];
    int sockfd;
    if (-1 == (sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP))) {
        printf("socket(): %s\n", strerror(errno));
        sleep(100);
        exit(1);
    }
    sleep(100);

    // icmp = (struct icmp*)sendbuff;
	// icmp->icmp_type = ICMP_ECHO;
	// icmp->icmp_code = 0;
	// icmp->icmp_cksum = 0;
	// icmp->icmp_id = 2;
	// icmp->icmp_seq = 3;

    // printf("buff is %x.\n", *sendbuff);
	
	// while(1) {	
	//     sendto(sockfd, sendbuff, 8, 0, (struct sockaddr *)&target, sizeof(target));
	//     sleep(1);
	// }

	// close(sockfd);

    return 0;
}