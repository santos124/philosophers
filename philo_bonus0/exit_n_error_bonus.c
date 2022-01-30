#include "philo_bonus.h"

int	liberator(t_room *room, int code)
{
	int	i;
	int	j;
	// int	f;

	i = -1;
	// if (!room->p_id)
	// {
	// 	sem_post(room->sema3);
	// 	exit(0);
	// }
	// sem_wait(room->sema3);
	sem_wait(room->sema3);
	if (room)
	{
		while (++i < room->n_phils)
		{
			j = -1;
			while (++j < room->n_phils)
			{
				kill(room->phil[j].p_id, SIGTERM);
			}
		}
		sem_close(room->printer);
		sem_close(room->forks);
		sem_unlink("/sem_forks");
		sem_unlink("/sem_printer");
		sem_close(room->sema3);
		sem_unlink("/sem_sema3");
		free(room->phil);
		free(room);
	}
	usleep(100000);
	return (code);
}

int	error_checker(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}
