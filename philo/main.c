/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:29:46 by wadina            #+#    #+#             */
/*   Updated: 2022/01/30 20:29:49 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_pthread(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->n_phils)
	{
		if ((pthread_create(&room->phils[i].tr, NULL, f_phil, &room->phils[i]))
			!= 0)
			return (1);
		i++;
	}
	milisleep(10);
	room->start = 1;
	i = 0;
	while (i < room->n_phils)
	{
		gettimeofday(&room->phils[i].dinner, NULL);
		i++;
	}
	gettimeofday(&room->t1, NULL);
	if ((pthread_create(&room->sentinel_t, NULL, ft_sentinel, room)) != 0)
		return (1);
	ft_death(room);
	return (0);
}

static void	ft_free(t_room *room)
{
	int	i;

	i = 0;
	if (room)
	{
		if (room->phils)
		{
			free(room->phils);
			room->phils = NULL;
		}
		if (room->f_mu)
		{
			while (i < room->n_phils)
			{
				pthread_mutex_destroy(&room->f_mu[i]);
				i++;
			}
			pthread_mutex_destroy(&room->mu_print);
			free(room->f_mu);
			room->f_mu = NULL;
		}
		free(room);
		room = NULL;
	}
}

static int	ft_exit(int status, t_room *room)
{
	ft_free(room);
	if (status != 0)
		write(2, "Error\n", 6);
	return (status);
}

int	main(int ac, char **av)
{
	t_room	*room;

	if (ac != 6 && ac != 5)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	room = init_room(ac, av);
	if (room == NULL)
		return (ft_exit(1, room));
	if ((start_pthread(room)) != 0)
		return (ft_exit(2, room));
	usleep(100);
	pthread_join(room->sentinel_t, NULL);
	return (ft_exit(0, room));
}
