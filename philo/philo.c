/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:33:36 by wadina            #+#    #+#             */
/*   Updated: 2022/01/30 20:33:38 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_forks(t_phil *phil, t_room *room)
{
	pthread_mutex_lock(&room->f_mu[phil->f_f]);
	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	ft_printer(phil, room);
	pthread_mutex_lock(&room->f_mu[phil->s_f]);
	phil->state = GET_FORK;
	phil->status = "has taken a fork";
	ft_printer(phil, room);
}

static int	do_think(t_phil *phil, t_room *room)
{
	phil->state = THINK;
	phil->status = "is thinking";
	ft_printer(phil, room);
	return (0);
}

static int	do_eat(t_phil *phil, t_room *room)
{	
	gettimeofday(&phil->dinner, NULL);
	phil->n_e++;
	phil->state = EAT;
	phil->status = "is eating";
	ft_printer(phil, room);
	milisleep(room->t_eat);
	pthread_mutex_unlock(&(room->f_mu[phil->s_f]));
	pthread_mutex_unlock(&(room->f_mu[phil->f_f]));
	return (0);
}

static int	do_sleep(t_phil *phil, t_room *room)
{
	phil->state = SLEEP;
	phil->status = "is sleeping";
	ft_printer(phil, room);
	milisleep(room->t_sleep);
	return (0);
}

void	*f_phil(void *p)
{
	t_phil	*phil;

	phil = (t_phil *)p;
	while (!phil->room->start)
		usleep(50);
	while (phil->room->death == -1 && phil->room->hungry == 1)
	{
		usleep(100);
		do_think(phil, phil->room);
		while (phil->can_eat != 1)
			usleep(200);
		get_forks(phil, phil->room);
		do_eat(phil, phil->room);
		phil->can_eat = 0;
		do_sleep(phil, phil->room);
	}
	pthread_detach(phil->tr);
	return (NULL);
}
