#include "philo_bonus.h"

int	get_processes2(t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < phil->room->n_phils)
	{
		if (i % 2 != 0)
		{
			phil[i].p_id = fork();
			if (phil[i].p_id < 0)
				exit (1);
			if (phil[i].p_id == 0)
			{
				processes(&(phil[i]));
				exit (1);
			}
		}
		usleep(150);
	}
	return (0);
}

int	get_processes(t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < phil->room->n_phils)
	{
		if (i % 2 == 0)
		{
			phil[i].p_id = fork();
			if (phil[i].p_id < 0)
				return (1);
			if (phil[i].p_id == 0)
			{
				processes(&(phil[i]));
				exit (1);
			}
		}
		usleep(150);
	}
	if (get_processes2(phil))
		return (1);
	return (0);
}

void	processes(void *phil0)
{
	t_phil			*phil;

	phil = phil0;
	if (pthread_create(&phil->tr, NULL, sentinel, phil))
		exit (1);
	
	while (phil->room->died == 0)
	{
		eat(phil);
		if (phil->count >= phil->room->n_must_eat
			&& phil->room->n_must_eat != -1)
		{
			sem_post(phil->room->sema3);
			break ;
		}
			
		printf("%llu %d %s\n", get_time() - phil->room->start,
			phil->id, "is sleeping");
		milisleep(phil->room->t_sleep);
		printf("%llu %d %s\n", get_time() - phil->room->start,
			phil->id, "is thinking");
	}
	pthread_join(phil->tr, NULL);
	exit(0);
}

int	main(int ac, char **av)
{
	t_room	*room;

	if (ac != 5 && ac != 6)
	{
		printf("%s\n", "wrong number of arguments");
		return (1);
	}
	if (error_checker(av))
		exit (1);
	room = room_init(ac, av);
	if (!room)
		exit (liberator(room, 1));
	if (get_processes(room->phil))
		exit (liberator(room, 1));
	return (liberator(room, 0));
}
