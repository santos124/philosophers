#include "philo.h"

void milisleep(int ms)
{
	t_time t1;
	t_time t2;

	gettimeofday(&t1, NULL);
	gettimeofday(&t2, NULL);
	while (get_time(t1, t2) < (long long)ms)
	{
		usleep(100);
		gettimeofday(&t2, NULL);
	}
}

long long get_ms(t_time t1)
{
	return (t1.tv_sec * 1000 + (t1.tv_usec / 1000));
}

long long get_time(t_time t1, t_time t2)
{
	return (long long)((t2.tv_sec * 1000 + (t2.tv_usec / 1000)) - (t1.tv_sec * 1000 + (t1.tv_usec / 1000)));
}

void	ft_printer(t_phil *phil, t_room *room)
{
	
	gettimeofday(&phil->room->t2, NULL);
	if (room->death == -1)
	{
		printf("%llu %d %s\n", get_time(phil->room->t1, phil->room->t2), phil->id, phil->status);
	}
	else if (room->death == phil->ind && phil->state == DIE)
	{
		pthread_mutex_lock(&room->mu_print);
		ft_putnbr_fd(get_time(phil->room->t1, phil->room->t2), 1);
		write(1, " ", 2);
		ft_putnbr_fd(phil->id, 1);
		write(1, " ", 2);
		ft_putstr_fd(phil->status, 1);
		write(1, "\n", 2);
		pthread_mutex_unlock(&room->mu_print);
	}
	phil->state = 0;
	
}
