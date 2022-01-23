#include "philo.h"

uint64_t get_time(t_time t1, t_time t2)
{

	return (t2.tv_sec * 1000 + (t2.tv_usec / 1000)) - (t1.tv_sec * 1000 + (t1.tv_usec / 1000));
}

void 	*get_fork(void *ptr)
{
	t_phil *phil;
	t_room *room;

	phil = (t_phil *)ptr; 
	room = (t_room *)phil->room;

	pthread_mutex_lock(&room->forks[phil->l_f].mu);
	room->forks[phil->l_f].use = phil->id;

	gettimeofday(&phil->t_fork1, NULL);

	while (room->forks[phil->r_f].use != 0)
	{

		usleep(phil->id);
		gettimeofday(&phil->t_fork2, NULL);
		if (get_time(phil->t_fork1, phil->t_fork2) > 50)
		{
			pthread_mutex_unlock(&room->forks[phil->l_f].mu);
			room->forks[phil->l_f].use = 0;
			return ((void*)1);
		}
	}
	pthread_mutex_lock(&room->forks[phil->r_f].mu);
	room->forks[phil->r_f].use = phil->id;	
	return (NULL);
}



int do_drop(t_phil *phil, t_room *room)
{
	pthread_mutex_unlock(&room->forks[phil->l_f].mu);
	room->forks[phil->l_f].use = 0;
	pthread_mutex_unlock(&room->forks[phil->r_f].mu);
	room->forks[phil->r_f].use = 0;
	return 0;
}

int do_think(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;
	phil->state = THINK;
	phil->status = "is thinking";
	printer(phil);
	return 0;
}

int		do_eat(t_phil *phil, t_room *room)
{
	(void)phil;
	(void)room;
	
	
	gettimeofday(&phil->t1, NULL);
	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	printer(phil);
	printer(phil);
	phil->n_e++;
	phil->state = EAT;
	phil->status = "is eating";
	printer(phil);
	usleep(room->t_eat);
	return 0;
}

int do_sleep(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;
	phil->state = SLEEP;
	phil->status = "is sleeping";
	printer(phil);
	usleep(room->t_sleep);
	
	return 0;
}
