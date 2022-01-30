/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:29:30 by wadina            #+#    #+#             */
/*   Updated: 2022/01/30 20:29:31 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_get_f_s_f(t_room *room, t_phil *phil)
{
	if (phil->ind % 2 == 0)
	{
		if (phil->ind == 0)
			phil->s_f = room->n_phils - 1;
		else
			phil->s_f = phil->ind - 1;
		phil->f_f = phil->ind;
	}
	else
	{
		if (phil->ind == 0)
			phil->f_f = room->n_phils - 1;
		else
			phil->f_f = phil->ind - 1;
		phil->s_f = phil->ind;
	}
}

static int	init_phils_mutexes(t_room *room)
{
	int	i;

	i = 0;
	room->death = -1;
	room->hungry = 1;
	while (i < room->n_phils)
	{
		room->phils[i].can_eat = 0;
		room->phils[i].id = i + 1;
		room->phils[i].ind = i;
		room->phils[i].state = 0;
		room->phils[i].room = room;
		ft_get_f_s_f(room, &room->phils[i]);
		if ((pthread_mutex_init(&(room->f_mu[i]), NULL)) != 0)
			return (1);
		i++;
	}
	if ((pthread_mutex_init(&room->mu_print, NULL)) != 0)
		return (1);
	return (0);
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

static int	parse_args(t_room *room, int ac, char **av)
{
	room->n_phils = ft_atoi(av[1]);
	if (room->n_phils < 1)
		return (1);
	if (get_num(2, av[2], &room->t_die))
		return (1);
	if (get_num(3, av[3], &room->t_eat))
		return (1);
	if (get_num(4, av[4], &room->t_sleep))
		return (1);
	if (ac == 6)
	{
		room->n_must_eat = ft_atoi(av[5]);
		if (room->n_must_eat < 1)
			return (1);
	}
	else
		room->n_must_eat = -1;
	return (0);
}

t_room	*init_room(int ac, char **av)
{
	t_room	*room;

	room = malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	*room = (t_room){0};
	if (parse_args(room, ac, av))
		return (NULL);
	room->phils = ft_calloc(sizeof(t_phil), room->n_phils + 1);
	if (!room->phils)
		return (NULL);
	room->f_mu = ft_calloc(sizeof(pthread_mutex_t), room->n_phils + 1);
	if (!room->f_mu)
		return (NULL);
	if (init_phils_mutexes(room))
		return (NULL);
	return (room);
}
