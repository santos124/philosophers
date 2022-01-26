#include "philo.h"


void 	get_forks(t_phil *phil, t_room *room)
{
	pthread_mutex_t *forks = phil->room->f_mu;

	pthread_mutex_lock(&forks[phil->l_f]);
	
	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	ft_printer(phil, room);

	pthread_mutex_lock(&forks[phil->r_f]);

	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	ft_printer(phil, room);
}



int do_drop(t_phil *phil, t_room *room)
{

	pthread_mutex_unlock(&(room->f_mu[phil->r_f]));
	pthread_mutex_unlock(&(room->f_mu[phil->l_f]));
	return 0;
}

int do_think(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;

	phil->state = THINK;
	phil->status = "is thinking";
	ft_printer(phil, room);
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
	ft_printer(phil, room);
	milisleep(room->t_eat);
	return 0;
}

int do_sleep(t_phil *phil, t_room *room)
{
	phil->state = SLEEP;
	phil->status = "is sleeping";
	ft_printer(phil, room);
	milisleep(room->t_sleep);
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

unsigned long long get_time(t_time t1, t_time t2)
{

	return (t2.tv_sec * 1000 + (t2.tv_usec / 1000)) - (t1.tv_sec * 1000 + (t1.tv_usec / 1000));
}