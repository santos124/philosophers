#include "philo.h"

void	*get_fork_l(void *ptr)
{
	t_phil *phil;
	t_room *room;


	phil = (t_phil *)ptr; 
	room = (t_room *)phil->room;
	pthread_mutex_lock(&room->forks[phil->ind].mu);
	room->forks[phil->ind].use = phil->id;

	while (room->forks[phil])
	{
		
	}
	return (0);
}

void	*get_fork_r(void *ptr)
{
	t_phil *phil;
	t_room *room;

	phil = (t_phil *)ptr; 
	room = (t_room *)phil->room;
	if (phil->id == 1)
		pthread_mutex_lock(&room->forks[room->n_phils - 1].mu);
	else
		pthread_mutex_lock(&room->forks[phil->id - 2].mu);
	return (0);
}


int do_get(t_phil *phil, t_room *room)
{
	while (room->forks[phil->l_f].use != phil->ind || room->forks[phil->r_f].use != phil->ind)
	{
		pthread_create(&phil->tr_l, NULL, get_fork_l, phil);
		pthread_join(phil->tr_l, NULL);
		usleep(100);
	}
	return 0;
}

int do_drop(t_phil *phil, t_room *room)
{
	pthread_mutex_unlock(&room->forks[phil->id - 1].mu);
	if (phil->id == 1)
		pthread_mutex_unlock(&room->forks[room->n_phils - 1].mu);
	else
		pthread_mutex_unlock(&room->forks[phil->id - 2].mu);
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
	// printf("%d t1=%lld\n", phil->n, (uint64_t)(phil->t1.tv_usec / 1000) + (phil->t1.tv_sec * 1000));
	
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
