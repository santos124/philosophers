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
void	*ft_phil(void *p)
{
	t_phil	*phil = (t_phil *)p;
	t_room *room = phil->room;
	gettimeofday(&phil->t1, NULL);
	printf("Philosoph is alive\n");
	while (1)
	{
		gettimeofday(&phil->t2, NULL);
		printf("%ld, %d\n", phil->t2.tv_sec - phil->t1.tv_sec, phil->t2.tv_usec - phil->t1.tv_usec);
		printf("Philosoph %d is thinking\n", phil->n);

		printf("Philosoph %d is eating in %d times\n", phil->n, phil->n_e);
		usleep(room->t_eat);
		phil->n_e++;
		printf("Philosoph %d is sleeping\n", phil->n);
		usleep(room->t_sleep);
	}
	return (NULL);
}

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
		pthread_mutex_init(&room->forks[i].mu, NULL);
		i++;
	}
	i = 0;
	
	
	
	
	
	return (room);
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
	while (i < room->n_phils)
	{
		pthread_create(&room->phils[i].tr, NULL, ft_phil, &room->phils[i]);
		i++;
	}
	sleep(19);
	exit(0);
	return (0);
}
