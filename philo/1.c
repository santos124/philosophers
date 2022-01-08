#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <conio.h>
 
#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS        0
 
void* helloWorld(void *args) {
    printf("Hello from thread!\n");
    return SUCCESS;
}
 

 void	*ft_phil(void *p)
{
	t_phil	*phil = (t_phil *)p;
	t_room *room = phil->room;
	gettimeofday(&phil->t1, NULL);

	printf("Philosoph %d is alive\n", phil->n);
	while (1)
	{
		


	//берем вилки
		while (room->forks[phil->n - 1].use || room->forks[phil->n - 2].use)
		{
			gettimeofday(&phil->t2, NULL);
			if (phil->t2.tv_usec - phil->t2.tv_usec > room->t_die)
			{
				printf("Philosoph %d is DEATH OT GOLODA\n", phil->n);
			}
		}

		pthread_mutex_lock(&room->forks[phil->n - 1].mu);
		room->forks[phil->n - 1].use = phil->n;
		if (phil->n != 0)
		{
			pthread_mutex_lock(&room->forks[phil->n - 2].mu);
			room->forks[phil->n - 2].use = phil->n;
		}
		else
		{
			pthread_mutex_lock(&room->forks[room->n_phils - 1].mu);
			room->forks[room->n_phils - 1].use = phil->n;
		}
		printf("Philosoph %d is eating in %d times\n", phil->n, phil->n_e);
		usleep(room->t_eat);

	//кладем вилки
		pthread_mutex_unlock(&room->forks[phil->n - 1].mu);
		if (phil->n != 0)
		{
			pthread_mutex_unlock(&room->forks[phil->n - 2].mu);
		}
		else
		{
			pthread_mutex_unlock(&room->forks[room->n_phils - 1].mu);
		}

		phil->n_e++;

		printf("Philosoph %d is sleeping\n", phil->n);
		usleep(room->t_sleep);
	}

	return (NULL);
}

//init_room
t_room		*init_room(int ac, char **av)
{
	t_room	*room;

	if (ac == 5)
		write(1, "4 agrs\n", 8);
	else
		write(1, "5 args\n", 8);
	room = malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	*room = (t_room){0};
	room->n_phils = ft_atoi(av[1]);
	room->t_die = ft_atoi(av[2]);
	room->t_eat = ft_atoi(av[3]);
	room->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		room->n_must_eat = ft_atoi(av[1]);
	room->phils = ft_calloc(sizeof(t_phil), room->n_phils + 1);
	if (!room->phils)
		return (NULL);
	room->forks = ft_calloc(sizeof(t_fork), room->n_phils + 1);
	if (!room->forks)
		return (NULL);
	int i = 0;
	while (i  < room->n_phils)
	{
		room->phils[i].n = i + 1;
		room->phils[i].room = room;
		pthread_mutex_init(&room->forks[i].mu, NULL);
		i++;
	}
	i = 0;
	
	
	
	
	
	return (room);
}

int main() {
    pthread_t thread;
    int status;
    int status_addr;
 
    status = pthread_create(&thread, NULL, helloWorld, NULL);
    if (status != 0) {
        printf("main error: can't create thread, status = %d\n", status);
        exit(ERROR_CREATE_THREAD);
    }
    printf("Hello from main!\n");
 
    status = pthread_join(thread, (void**)&status_addr);
    if (status != SUCCESS) {
        printf("main error: can't join thread, status = %d\n", status);
        exit(ERROR_JOIN_THREAD);
    }
 
    printf("joined with address %d\n", status_addr);
    _getch();
    return 0;
}
