//#include "/tmp/rctx.h"

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>

#define JSSWITCHES 16

struct rcdata_s {
	unsigned int chan1 : 11;
	unsigned int chan2 : 11;
	unsigned int chan3 : 11;
	unsigned int chan4 : 11;
	unsigned int chan5 : 11;
	unsigned int chan6 : 11;
	unsigned int chan7 : 11;
	unsigned int chan8 : 11;
	unsigned int switches : 16;
} __attribute__ ((__packed__));


void main (void) {
#ifdef JSSWITCHES  // 

//	uint16_t *rcdata = 0; // 
	struct rcdata_s *rcdata = NULL;
	void *retval;
	
	int fd = shm_open("/wifibroadcast_rc_channels", O_RDWR, S_IRUSR | S_IWUSR);
	if(fd >= 0) {
		if (ftruncate(fd, sizeof(struct rcdata_s)) != -1) {
			retval = mmap(NULL, sizeof(struct rcdata_s), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
			if (retval != MAP_FAILED) {
				rcdata = (struct rcdata_s *)retval;			}
		}
	}
	if (rcdata == NULL)	{	//Error
		printf("-1\n");
	} else
		printf("%d\n",rcdata->switches);
#else
	printf("-1\n");
#endif
}