#include "philo.h"

int	ft_hungry(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->n_phils)
	{
		if (room->phils[i].n_e != room->n_must_eat)
			return (1);
		i++;
	}
	return (0);
}

void	ft_death(t_room *room)
{
	int	i;

	while ((room->death == -1) && ft_hungry(room))
	{
		usleep(5000);
		i = 0;
		while (i < room->n_phils)
		{
			usleep(50);
			gettimeofday(&room->death_t, NULL);
			if (room->phils[i].n_e != room->n_must_eat
				&& get_time(room->phils[i].dinner, room->death_t)
				>= room->t_die)
			{
				room->death = i;
				room->phils[i].state = DIE;
				room->phils[i].status = "died";
				ft_printer(&room->phils[i], room);
				return ;
			}
			i++;
		}
	}
}
