#include "philo.h"

static int	check_eat(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->n_phils - 1)
	{
		if (room->phils[i].can_eat == 1)
			return (1);
		i += 2;
	}
	return (0);
}

static int	check_eat2(t_room *room)
{
	int	i;

	i = 1;
	while (i < room->n_phils)
	{
		if (room->phils[i].can_eat == 1)
			return (1);
		i += 2;
	}
	return (0);
}

static void	check_eat3(t_room *room)
{
	while (room->n_phils % 2 == 1 && room->death == -1)
	{
		usleep(500);
		if (room->n_phils % 2 == 1
			&& room->phils[room->n_phils - 1].can_eat == 1)
			break ;
	}
}

static void	last_men(t_room *room)
{
	if (room->n_phils % 2 == 1)
	{
		room->phils[room->n_phils - 1].can_eat = 1;
	}
}

void	*ft_sentinel(void *ptr)
{
	t_room	*room;
	int		i;

	room = ptr;
	while (room->death == -1 && ft_hungry(room))
	{
		i = 0;
		while (i < room->n_phils - 1)
		{
			room->phils[i].can_eat = 1;
			i += 2;
		}
		while (check_eat(room) && room->death == -1)
			usleep(500);
		i = 0;
		while (++i < room->n_phils)
			room->phils[i++].can_eat = 1;
		while (check_eat2(room) && room->death == -1)
			usleep(500);
		last_men(room);
		check_eat3(room);
	}
	return (0);
}
