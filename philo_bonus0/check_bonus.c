#include "philo_bonus.h"

int	ft_death(t_phil *phil)
{
	
	if (!phil->is_eating && ((get_time() - phil->eat_last) > phil->room->t_die))
	{
		sem_wait(phil->room->printer);
		usleep(1000);
		phil->room->died++;
		if (phil->room->died == 1)
			printf("%llu %d %s\n", get_time()
				- phil->room->start, phil->id, "died");
		sem_post(phil->room->printer);
		return (1);
	}
	else if ((phil->room->t_die < phil->room->t_eat
			|| phil->room->t_die < phil->room->t_eat)
		&& get_time() - phil->room->start >= phil->room->t_die)
	{
		sem_wait(phil->room->printer);
		usleep(1000);
		phil->room->died++;
		if (phil->room->died == 1)
			printf("%llu %d %s\n", get_time() - phil->room->start,
				phil->id, "died");
		sem_post(phil->room->printer);
		return (1);
	}
	
	return (0);
}

void	*sentinel(void *phil0)
{
	t_phil	*phil;

	phil = phil0;
	while (1)
	{
		if (ft_death(phil))
		{
			pthread_detach(phil->tr);
			sem_post(phil->room->sema3);
			return (NULL);
		}

		usleep(100);
	}
}
