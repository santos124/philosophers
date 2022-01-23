

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

static pthread_mutex_t mu;
struct timeval t1;
struct timeval t2;
int a = 0;
uint64_t get_time(struct timeval t1, struct timeval t2)
{
	return (t2.tv_sec * 1000 + (t2.tv_usec / 1000)) - (t1.tv_sec * 1000 + (t1.tv_usec / 1000));
}
    pthread_t thread_1;
	pthread_t thread_2;
	int i = 0;
void *fun_pthread(void *ptr)
{
	
	// printf("pthread 1 a=%d, %p\n", *a_ptr, a_ptr);

	while(a < 100000)
	{
		pthread_mutex_lock(&mu);
		a++;
		pthread_mutex_unlock(&mu);
		usleep(1);
	}
		
	// printf("pthread 2 a=%d, %p\n", *a_ptr, a_ptr);
	
	return (NULL);
}

void *fun_pthread2(void *ptr)
{
	
	// printf("pthread 1 a=%d, %p\n", *a_ptr, a_ptr);
	sleep(5);
	while(a < 1000000)
	{
		pthread_mutex_lock(&mu);
		a++;
		pthread_mutex_unlock(&mu);
		usleep(1);
	}
		
	// printf("pthread 2 a=%d, %p\n", *a_ptr, a_ptr);
	
	return (NULL);
}

int main(int argc, char ** argv) {


	printf("1 a=%d, \n", a);

	pthread_mutex_init(&mu, NULL);

    pthread_create(&thread_1, NULL, fun_pthread, NULL);
	pthread_create(&thread_2, NULL, fun_pthread2, NULL);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	printf("2 a=%d, \n", a);
    return 0;
}

    // pthread_join(thread_1, NULL);