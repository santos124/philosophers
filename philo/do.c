#include "philo.h"

unsigned long long get_time(t_time t1, t_time t2)
{

	return (t2.tv_sec * 1000 + (t2.tv_usec / 1000)) - (t1.tv_sec * 1000 + (t1.tv_usec / 1000));
}

void 	get_fork(t_phil *phil)
{
	t_fork *forks = phil->room->forks;
	pthread_mutex_lock(&forks[phil->l_f].mu);
	
	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	pthread_create(&phil->tr, NULL, printer, phil);
	pthread_detach(phil->tr);

	pthread_mutex_lock(&forks[phil->r_f].mu);

	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	pthread_create(&phil->tr, NULL, printer, phil);
	pthread_detach(phil->tr);

}



int do_drop(t_phil *phil, t_room *room)
{

	pthread_mutex_unlock(&room->forks[phil->r_f].mu);
	pthread_mutex_unlock(&room->forks[phil->l_f].mu);
	return 0;
}

int do_think(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;

	phil->state = THINK;
	phil->status = "is thinking";
	pthread_create(&phil->tr, NULL, printer, phil);
	pthread_detach(phil->tr);
	return 0;
}

int		do_eat(t_phil *phil, t_room *room)
{
	(void)phil;
	(void)room;
	
	
	gettimeofday(&phil->dinner, NULL);
	phil->n_e++;

	phil->state = EAT;
	phil->status = "is eating";
	
	pthread_create(&phil->tr, NULL, printer, phil);
	pthread_detach(phil->tr);
	milisleep(room->t_eat / 1000);
	return 0;
}

void milisleep(int ms)
{
	t_time t1;
	t_time t2;
	gettimeofday(&t1, NULL);
	gettimeofday(&t2, NULL);
	while (get_time(t1, t2) < (unsigned long long)ms)
	{
		usleep(100);
		gettimeofday(&t2, NULL);
	}
}

int do_sleep(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;

	phil->state = SLEEP;
	phil->status = "is sleeping";
	pthread_create(&phil->tr, NULL, printer, phil);
	pthread_detach(phil->tr);
	milisleep(room->t_sleep / 1000);
	// usleep(room->t_sleep);
	return 0;
}
