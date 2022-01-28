

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>


struct timeval t1;
struct timeval t2;


int main(int argc, char ** argv) {
	
	
	gettimeofday(&t1, NULL);


	printf("a=%d %d, \n", t1.tv_usec, t2.tv_usec);
	usleep(100);
	t2 = t1;
	usleep(100);
	gettimeofday(&t1, NULL);
	printf("a=%d %d, \n", t1.tv_usec, t2.tv_usec);


    return 0;
}

    // pthread_join(thread_1, NULL);