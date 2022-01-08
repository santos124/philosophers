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

//check_ptr
int check_ptr(void *ptr)
{
	if (!ptr)
		return (1);
	return (0);
}


//phil
void	*f_phil(void *p)
{
	t_phil	*phil = (t_phil *)p;
	// t_room *room = phil->room;
	gettimeofday(&phil->t1, NULL);

	printf("Philosoph %d is alive\n", phil->n);
	while (1)
	{
		do_get(phil);
		do_drop(phil, phil->room);
		do_eat(phil, phil->room);
		do_think(phil, phil->room);
		do_sleep(phil, phil->room);
	}

	return (NULL);
}
void *f_watch(void *ptr)
{
	t_room *room;
	room = (t_room *)ptr;

	return (0);
}

// void *f_fork(void *ptr)
// {
// 	t_room *room;
// 	room = (t_room *)ptr;

// 	return (0);
// }

//init_room
t_room		*init_room(int ac, char **av)
{
	t_room	*room;

	if (ac == 5)
		write(1, "4 agrs\n", 8);
	else
		write(1, "5 args\n", 8);
	room = malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	*room = (t_room){0};
	room->n_phils = ft_atoi(av[1]);
	room->t_die = ft_atoi(av[2]);
	room->t_eat = ft_atoi(av[3]);
	room->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		room->n_must_eat = ft_atoi(av[1]);
	room->phils = ft_calloc(sizeof(t_phil), room->n_phils + 1);
	if (!room->phils)
		return (NULL);
	room->forks = ft_calloc(sizeof(t_fork), room->n_phils + 1);
	if (!room->forks)
		return (NULL);
	int i = 0;
	while (i  < room->n_phils)
	{
		room->phils[i].n = i + 1;
		room->phils[i].room = room;
		room->forks[i].room = room;
		pthread_mutex_init(&room->forks[i].mu, NULL);
		i++;
	}
	return (room);
}



int init_pthread(t_room *room)
{
	int i = 0;

	pthread_create(&room->watch, NULL, f_watch, room);
	while (i < room->n_phils)
	{
		pthread_create(&room->phils[i].tr, NULL, f_phil, &room->phils[i]);
		i++;
	}
	return 0;
}


//main
int	main(int ac, char **av)
{
	t_room	*room;
	int		i;

	i = 0;
	if (ac != 6 && ac != 5)
	{
		write(2, "Error\n need args\n", 18);
		return (0);
	}	
	room = init_room(ac, av);
	printf("%d %d %d %d %d\n", room->n_phils,  room->t_die, room->t_eat, room->t_sleep, room->n_must_eat);
	while (i < ac)
	{
		printf("av[%d]=%s\n", i, av[i]);
		if (i != 0)
		{
			ft_atoi(av[i]);
		}
		i++;
	}

	i = 0;
	init_pthread(room);
	
	sleep(5);
	return (0);
}
