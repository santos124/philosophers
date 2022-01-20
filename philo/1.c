// #include <stdio.h>
// #include <sys/time.h>
// #include <unistd.h>
// # include	<pthread.h>
// #include <stdlib.h>
// typedef struct	s_all
// {
// 	pthread_t		tr;
// 	pthread_t		tr2;
// 	pthread_mutex_t	mu;
// 	int				a;
// }				t_all;

// void *fn(void *ptr_raw)
// {
// 	t_all	*all = (t_all*)ptr_raw;
// 	write(1, "START\n", 7);
// 	pthread_mutex_lock(&all->mu);
// 	write(1, "MID\n", 5);
// 	sleep(2);
// 	write(1, "END\n", 5);
// 	pthread_mutex_unlock(&all->mu);
	
// 	return NULL;
// }

// int main()
// {
// 	t_all	*all = malloc(sizeof(t_all));

// 	pthread_mutex_init(&all->mu, NULL);
// 	pthread_create(&all->tr, NULL, fn, &all);
// 	pthread_create(&all->tr2, NULL, fn, &all);
// 	pthread_join(all->tr, NULL);
// 	pthread_join(all->tr2, NULL);
// 	printf("MAIN \n");
// 	return 0;
// }

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

static int counter; // shared resource
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void incr_counter(void *p) {
    do {
		printf("PRIVET CONT!\n");
        usleep(10); // Let's have a time slice between mutex locks
        pthread_mutex_lock(&mutex);
        counter++;
        printf("%d\n", counter);
        sleep(5);
		printf("POKA CONT!\n");

        pthread_mutex_unlock(&mutex);
    } while ( 1 );
}

void reset_counter(void *p) {
    char buf[10];
    int  num = 0;
    int  rc;
    pthread_mutex_lock(&mutex); // block mutex just to show message
    printf("Enter the number and press 'Enter' to initialize the counter with new value anytime.\n");
    // sleep(3);
    pthread_mutex_unlock(&mutex); // unblock blocked mutex so another thread may work
    do {
		            
		printf("PRIVET RESET!\n");

        if ( gets(buf) != buf ) return; // NO fool-protection ! Risk of overflow !
        num = atoi(buf);
        if ( (rc = pthread_mutex_trylock(&mutex)) == EBUSY ) {
            printf("Mutex is already locked by another process.\nLet's lock mutex using pthread_mutex_lock().\n");
            pthread_mutex_lock(&mutex);
        } else if ( rc == 0 ) {
            printf("WOW! You are on time! Congratulation!\n");
        } else { 
            printf("Error: %d\n", rc);
            return;
        }
        counter = num;
        printf("New value for counter is %d\n", counter);
		printf("POKA RESET!\n");
        pthread_mutex_unlock(&mutex);
    } while ( 1 );
}

int main(int argc, char ** argv) {
    pthread_t thread_1;
    pthread_t thread_2;
    counter = 0;

    pthread_create(&thread_1, NULL, (void *)&incr_counter, NULL);
    pthread_create(&thread_2, NULL, (void *)&reset_counter, NULL);

    pthread_join(thread_2, NULL);
    return 0;
}