#include "philo_bonus.h"

void	eat(t_phil *phil)
{
	sem_wait(phil->room->forks);
	printf("%llu %d %s\n", get_time() - phil->room->start,
		phil->id, "has taken a fork");
	sem_wait(phil->room->forks);
	printf("%llu %d %s\n", get_time() - phil->room->start,
		phil->id, "has taken a fork");
	phil->is_eating = 1;
	phil->count++;
	phil->eat_last = get_time();
	printf("%llu %d %s\n", get_time() - phil->room->start,
		phil->id, "is eating");
	milisleep(phil->room->t_eat);
	phil->is_eating = 0;
	sem_post(phil->room->forks);
	sem_post(phil->room->forks);
	
}
