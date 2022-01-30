/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:29:20 by wadina            #+#    #+#             */
/*   Updated: 2022/01/30 20:30:19 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	room->hungry = ft_hungry(room);
	while ((room->death == -1) && room->hungry == 1)
	{
		room->hungry = ft_hungry(room);
		usleep(50);
		i = 0;
		while (i < room->n_phils)
		{
			usleep(100);
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
