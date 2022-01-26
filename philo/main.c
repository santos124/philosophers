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
void	*f_phil(void *p)
{
	t_phil	*phil = (t_phil *)p;
	t_room *room = phil->room;

	while (!room->start)
	{
	}

	gettimeofday(&phil->dinner, NULL);
	while (room->death == -1)
	{
		
		while (room->eat_group != phil->group)
		{
			// printf("xyu\n");
			milisleep(1);
		}
		do_think(phil, phil->room);
		get_forks(phil, room);
		do_eat(phil, room);
		phil->can_eat = 0;
		do_drop(phil, room);
		do_sleep(phil, phil->room);
	}
	return (NULL);
}

void	ft_printer(t_phil *phil, t_room *room)
{
	pthread_mutex_lock(&room->mu_print);
	gettimeofday(&phil->room->t2, NULL);
	printf("%llu %d %s\n", get_time(phil->room->t1, phil->room->t2), phil->id, phil->status);
	phil->state = 0;
	pthread_mutex_unlock(&room->mu_print);
}


int		some_dead(t_room *room)
{
	int i;

	i = 0;
	while (i < room->n_phils)
	{
		if (room->phils[i].state == DIE)
		{
			room->death = room->phils[i].id;
			return (1);
		}
		i++;
	}
	return (0);
}


void	ft_get_group(t_room *room, t_phil *phil)
{

	if (phil->id == room->n_phils && room->n_phils % 2 == 1)
	{
		phil->group = 3;
	}
	else
	{
		phil->group = 1 + phil->ind % 2;
	}
}

void ft_get_l_r_f(t_room *room, t_phil *phil)
{
	if (phil->ind % 2 == 0)
	{
		if (phil->ind == 0)
			phil->r_f = room->n_phils - 1;
		else
			phil->r_f = phil->ind - 1;
		phil->l_f = phil->ind;
	}
	else
	{
		if (phil->ind == 0)
			phil->l_f = room->n_phils - 1;
		else
			phil->l_f = phil->ind - 1;
		phil->r_f = phil->ind;
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
	room->n_phils = ft_atoi(av[1]);
	room->t_die = ft_atoi(av[2]);
	room->t_eat = ft_atoi(av[3]);
	room->t_sleep = ft_atoi(av[4]);
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
		ft_get_group(room, &room->phils[i]);
		ft_get_l_r_f(room, &room->phils[i]);
		pthread_mutex_init(&(room->f_mu[i]), NULL);
		i++;
	}
	pthread_mutex_init(&room->mu_print, NULL);
	return (room);
}


static int	ft_sentinel(t_room *room)
{
	int i;
	t_time t1;
	
	while (room->death == 0)
	{
		
		i = 0;
		milisleep(1);
		
		

		while (i < room->n_phils)
		{
			gettimeofday(&t1, NULL);
			if (get_time(room->phils[i].dinner, t1) >= room->t_die)
			{
				room->death = i;
				milisleep(100);
				exit(0);
			}

			i++;
		}
	}
	return 0;
}


static int init_pthread(t_room *room)
{
	int i = 0;

	
	while (i < room->n_phils)
	{
		pthread_create(&room->phils[i].tr, NULL, f_phil, &room->phils[i]);
		i++;
	}
	milisleep(228);
	gettimeofday(&room->t1, NULL);
	room->start = 1;
	milisleep(120);
	
	return 0;
}


int	main(int ac, char **av)
{

	t_room	*room;

	if (ac != 6 && ac != 5)
	{
		write(2, "Error\n need args\n", 18);
		return (0);
	}
	
	room = init_room(ac, av);
	init_pthread(room);
	
	ft_sentinel(room);
	
	return (0);
}



	// t_time t1;
	// t_time t2;
	// gettimeofday(&t1, NULL);
	// // usleep(1000000);
	// milisleep(1000);
	// gettimeofday(&t2, NULL);

	// printf("%llu PRIVET\n", get_time(t1, t2));
	// exit(0);



// void	*serve(void *ptr)
// {
// 	t_room	*room;
// 	int		i;
// 	int		min;
// 	room = (t_room *)ptr;
// 	i = 0;
// 	while (!some_dead(room))
// 	{
// 		i = 0;
// 		min = 100500;
// 		while (i < room->n_phils)
// 		{
			
// 			if (room->phils[i].n_e < min)
// 				min = room->phils[i].n_e;
// 			i++;
// 		}
// 		i = 0;
// 		while (i < room->n_phils)
// 		{
// 			if (room->phils[i].n_e == min && room->phils[i].can_eat == 0 && i % 2 == 0)
// 				room->phils[i].can_eat = 1;
// 			i++;
// 		}
// 		while (room->phils[2].can_eat == 1 || room->phils[0].can_eat == 1)
// 		{
// 		}
// 		i = 0;
// 		while (i < room->n_phils)
// 		{
// 			if (room->phils[i].n_e == min && room->phils[i].can_eat == 0 && i % 2 == 1)
// 				room->phils[i].can_eat = 1;
// 			i++;
// 		}
// 		while (room->phils[3].can_eat == 1 || room->phils[1].can_eat == 1)
// 		{
// 		}
// 	}
// 	exit(0);

// 	return (0);
// }