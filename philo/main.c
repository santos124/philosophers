/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:31:33 by wadina            #+#    #+#             */
/*   Updated: 2022/01/05 13:31:35 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//phil


static void ft_get_l_s_f(t_room *room, t_phil *phil)
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

//init_room
static t_room		*init_room(int ac, char **av)
{
	t_room	*room;

	room = malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	*room = (t_room){0};
	if ((room->n_phils = ft_atoi(av[1])) <= 0)
		return (NULL);
	if ((room->t_die = ft_atoi(av[2])) <= 0)
		return (NULL);
	if ((room->t_eat = ft_atoi(av[3])) <= 0)
		return (NULL);
	if ((room->t_sleep = ft_atoi(av[4])) <= 0)
		return (NULL);
	if (ac == 6)
		room->n_must_eat = ft_atoi(av[5]);
	else
		room->n_must_eat = -1;
	room->phils = ft_calloc(sizeof(t_phil), room->n_phils + 1);
	if (!room->phils)
		return (NULL);
	room->f_mu = ft_calloc(sizeof(pthread_mutex_t), room->n_phils + 1);
	if (!room->f_mu)
		return (NULL);
	int i = 0;
	room->death = -1;
	while (i  < room->n_phils)
	{
		room->phils[i].can_eat = 0;
		room->phils[i].id = i + 1;
		room->phils[i].ind = i;
		room->phils[i].state = 0;
		room->phils[i].room = room;
		ft_get_l_s_f(room, &room->phils[i]);
		pthread_mutex_init(&(room->f_mu[i]), NULL);
		i++;
	}
	pthread_mutex_init(&room->mu_print, NULL);
	return (room);
}



static int init_pthread(t_room *room)
{
	int i;
	
	i = 0;
	while (i < room->n_phils)
	{
		pthread_create(&room->phils[i].tr, NULL, f_phil, &room->phils[i]);
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
	pthread_create(&room->sentinel_t, NULL, ft_sentinel, room);
	ft_death(room);
	return (0);
}

void ft_free(t_room *room)
{
	int i;

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
			free(room->f_mu);
			room->f_mu = NULL;
		}
		
		free(room);
		room = NULL;
	}
}

int		ft_exit(int status, t_room *room)
{
	ft_free(room);
	if (status != 0)
		write(2, "Error\n", 24);
	return (status);
}
int	main(int ac, char **av)
{
	t_room	*room;

	if (ac != 6 && ac != 5)
	{
		write(2, "Error\n", 24);
		return (0);
	}
	
	if ((room = init_room(ac, av)) == NULL)
		return (ft_exit(1, room));
	init_pthread(room);
	usleep(100);
	pthread_join(room->sentinel_t, NULL);
	
	return (ft_exit(0, room));
}