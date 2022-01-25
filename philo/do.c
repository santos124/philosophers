#include "philo.h"

unsigned long long get_time(t_time t1, t_time t2)
{

	return (t2.tv_sec * 1000 + (t2.tv_usec / 1000)) - (t1.tv_sec * 1000 + (t1.tv_usec / 1000));
}

void 	get_fork(t_phil *phil)
{
	t_fork *forks = phil->room->forks;
	pthread_mutex_lock(&phil->room->forks[phil->l_f].mu);
	forks[phil->l_f].use = phil->id;
	pthread_mutex_lock(&phil->room->mu_print);
	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	gettimeofday(&phil->room->t2, NULL);
	ft_putnbr_fd(get_time(phil->room->t1, phil->room->t2), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(phil->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(phil->status, 1);
	ft_putstr_fd("\n", 1);
	phil->state = 0;
	pthread_mutex_unlock(&phil->room->mu_print);

	pthread_mutex_lock(&phil->room->forks[phil->r_f].mu);
	forks[phil->r_f].use = phil->id;
	pthread_mutex_lock(&phil->room->mu_print);
	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	gettimeofday(&phil->room->t2, NULL);
	ft_putnbr_fd(get_time(phil->room->t1, phil->room->t2), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(phil->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(phil->status, 1);
	ft_putstr_fd("\n", 1);
	phil->state = 0;
	pthread_mutex_unlock(&phil->room->mu_print);
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
	pthread_mutex_lock(&phil->room->mu_print);
	phil->state = THINK;
	phil->status = "is thinking";
	gettimeofday(&phil->room->t2, NULL);
	ft_putnbr_fd(get_time(phil->room->t1, phil->room->t2), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(phil->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(phil->status, 1);
	ft_putstr_fd("\n", 1);
	phil->state = 0;
	pthread_mutex_unlock(&phil->room->mu_print);
	return 0;
}

int		do_eat(t_phil *phil, t_room *room)
{
	(void)phil;
	(void)room;
	
	
	gettimeofday(&phil->dinner, NULL);

	phil->n_e++;

	pthread_mutex_lock(&phil->room->mu_print);
	phil->state = EAT;
	phil->status = "is eating";
	usleep(room->t_eat);
	gettimeofday(&phil->room->t2, NULL);
	ft_putnbr_fd(get_time(phil->room->t1, phil->room->t2), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(phil->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(phil->status, 1);
	ft_putstr_fd("\n", 1);
	phil->state = 0;
	pthread_mutex_unlock(&phil->room->mu_print);

	return 0;
}

int do_sleep(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;
	pthread_mutex_lock(&phil->room->mu_print);
	phil->state = SLEEP;
	phil->status = "is sleeping";
	usleep(room->t_sleep);
	gettimeofday(&phil->room->t2, NULL);
	ft_putnbr_fd(get_time(phil->room->t1, phil->room->t2), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(phil->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(phil->status, 1);
	ft_putstr_fd("\n", 1);
	phil->state = 0;
	pthread_mutex_unlock(&phil->room->mu_print);
	return 0;
}
