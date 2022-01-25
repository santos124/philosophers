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
	gettimeofday(&phil->dinner, NULL);

	while (room->death != 1)
	{
		do_think(phil, phil->room);
		// while (!phil->can_eat)
		// {
		// }
		get_fork(phil);
		do_eat(phil, room);
		phil->can_eat = 0;
		do_drop(phil, room);
		do_sleep(phil, phil->room);
	}
	return (NULL);
}

void	*printer(void *ptr)
{
	t_phil	*phil = ptr;
	t_room	*room = phil->room;
	pthread_mutex_lock(&room->mu_print);
	gettimeofday(&phil->room->t2, NULL);
	// printf("%llu %d %s\n", get_time(phil->room->t1, phil->room->t2), phil->id, phil->status);
	ft_putnbr_fd(get_time(phil->room->t1, phil->room->t2), 1);
	write(1, " ", 1);
	ft_putnbr_fd(phil->id, 1);
	write(1, " ", 1);
	ft_putstr_fd(phil->status, 1);
	write(1, "\n", 1);
	phil->state = 0;
	pthread_mutex_unlock(&room->mu_print);

	return (NULL);
}


int		some_dead(t_room *room)
{
	int i;

	i = 0;
	while (i < room->n_phils)
	{
		if (room->phils[i].state == DIE)
		{
			room->death = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	*f_palach(void *ptr)
{
	t_room	*room;
	int		i;

	room = (t_room *)ptr;
	i = 0;
	while (!some_dead(room))
	{
		i = 0;
		usleep(1000);
		while (i < room->n_phils)
		{
			// usleep(1);
			gettimeofday(&room->phils[i].check, NULL);
			if (get_time(room->phils[i].dinner, room->phils[i].check) >= room->t_die / 1000)
			{
				unsigned long long b = (room->phils[i].check.tv_usec / 1000) + (room->phils[i].check.tv_sec * 1000);
				unsigned long long a = (room->phils[i].dinner.tv_usec / 1000) + (room->phils[i].dinner.tv_sec * 1000);
				printf("phil[%d] %llu - %llu = %llu | %llu\n",i, b, a, b - a, room->t_die / 1000);
				// ft_putnbr_fd();
				// write(1, " ", 1);
				// write(1, "\n", 1);
				room->phils[i].state = DIE;
				room->phils[i].status = "died";
					pthread_create(&room->phils[i].tr, NULL, printer, &room->phils[i]);
					pthread_detach(room->phils[i].tr);

				exit(0);
			}
			i++;
		}
	}


	return (0);
}

// void	*serve(void *ptr)
// {
// 	t_room	*room;
// 	int		i;
// 	int		min;
// 	room = (t_room *)ptr;
// 	i = 0;
// 	while (!some_dead(room))
// 	{
// 		usleep(500);
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

//init_room
t_room		*init_room(int ac, char **av)
{
	t_room	*room;

	room = malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	*room = (t_room){0};
	room->n_phils = ft_atoi(av[1]);
	room->t_die = 1000 * ft_atoi(av[2]);
	room->t_eat = 1000 * ft_atoi(av[3]);
	room->t_sleep = 1000 * ft_atoi(av[4]);
	if (ac == 6)
		room->n_must_eat = ft_atoi(av[5]);
	else
		room->n_must_eat = -1;
	room->phils = ft_calloc(sizeof(t_phil), room->n_phils + 1);
	if (!room->phils)
		return (NULL);
	room->forks = ft_calloc(sizeof(t_fork), room->n_phils + 1);
	if (!room->forks)
		return (NULL);
	int i = 0;
	while (i  < room->n_phils)
	{
		room->phils[i].can_eat = 0;
		room->phils[i].id = i + 1;
		room->phils[i].ind = i;
		room->phils[i].state = 0;
		room->phils[i].room = room;
		if (i % 2 == 0)
		{
			if (i == 0)
				room->phils[i].r_f = room->n_phils - 1;
			else
				room->phils[i].r_f = room->phils[i].ind - 1;
			room->phils[i].l_f = room->phils[i].ind;
		}
		else
		{
			if (i == 0)
				room->phils[i].l_f = room->n_phils - 1;
			else
				room->phils[i].l_f = room->phils[i].ind - 1;
			room->phils[i].r_f = room->phils[i].ind;

			pthread_mutex_init(&room->phils[i].mu, NULL);
			
		}
		room->forks[i].room = room;
		room->forks[i].use = 0;
		pthread_mutex_init(&room->forks[i].mu, NULL);
		i++;
	}
	pthread_mutex_init(&room->mu_print, NULL);
	return (room);
}



int init_pthread(t_room *room)
{
	int i = 0;

	gettimeofday(&room->t1, NULL);
	while (i < room->n_phils)
	{
		pthread_create(&room->phils[i].tr, NULL, f_phil, &room->phils[i]);
		i++;
	}
	
	while (room->phils[room->n_phils - 1].dinner.tv_sec == 0)
	{
		// usleep(1);
	}
	
	// pthread_create(&room->serve, NULL, serve, room);
	pthread_create(&room->palach, NULL, f_palach, room);
	
	
	return 0;
}


//main
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
	
	pthread_join(room->palach, NULL);
	
	return (0);
}
