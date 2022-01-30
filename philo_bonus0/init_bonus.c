#include "philo_bonus.h"

t_phil	*phil_info(t_room *room)
{
	int	i;

	room->phil = malloc((sizeof(t_phil) * room->n_phils));
	i = 0;
	while (i < room->n_phils)
	{
		room->phil[i].id = i + 1;
		room->phil[i].room = room;
		room->phil[i].eat_last = get_time();
		room->phil[i].count = 0;
		room->phil[i].is_eating = 0;
		room->died = 0;
		i++;
	}
	return (room->phil);
}

static int	get_num(int num, char *av, long long *dig_ptr)
{
	*dig_ptr = ft_atoi(av);
	if (num == 1 && *dig_ptr < (long long)1)
		return (1);
	else if (num == 2 && *dig_ptr < (long long)60)
		return (1);
	else if (num == 3 && *dig_ptr < (long long)60)
		return (1);
	else if (num == 4 && *dig_ptr < (long long)60)
		return (1);
	else if (num == 5 && *dig_ptr < (long long)1)
		return (1);
	return (0);
}

static int	parse_args(t_room **room, int ac, char **av)
{
	if (ft_atoi(av[1]) < 1)
		return (1);
	*room = malloc(sizeof(t_room));
	if (!(*room))
		return (1);
	(*room)->n_phils = ft_atoi(av[1]);
	if ((*room)->n_phils < 1)
		return (1);
	if (get_num(2, av[2], &(*room)->t_die))
		return (1);
	if (get_num(3, av[3], &(*room)->t_eat))
		return (1);
	if (get_num(4, av[4], &(*room)->t_sleep))
		return (1);
	if (ac == 6)
	{
		(*room)->n_must_eat = ft_atoi(av[5]);
		if ((*room)->n_must_eat < 1)
			return (1);
	}
	else
		(*room)->n_must_eat = -1;
	(*room)->start = get_time();
	return (0);
}

t_room	*room_init(int ac, char **av)
{
	t_room		*room;
	int			i;

	i = -1;
	if (parse_args(&room, ac, av))
		return (NULL);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_printer");
	sem_unlink("/sema_sema3");
	room->forks = sem_open("/sem_forks", O_CREAT, S_IRWXU, room->n_phils);
	room->printer = sem_open("/sem_printer", O_CREAT, S_IRWXU, 1);
	room->sema3 = sem_open("/sema_sema3", O_CREAT, S_IRWXU, 0);
	room->phil = phil_info(room);
	if (!room->phil)
		return (NULL);
	return (room);
}
