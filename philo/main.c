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
int		check_ptr(void *ptr)
{
	if (!ptr)
		return (1);
	return (0);
}

int		closer(t_room *room)
{
	int i = 0;
	while (i < room->n_phils)
	{
		pthread_detach(room->phils[i].tr_l);
		pthread_detach(room->phils[i].tr_r);
		pthread_detach(room->phils[i].tr);
		i++;
	}
	

	return 0;
}

//phil
void	*f_phil(void *p)
{
	t_phil	*phil = (t_phil *)p;
	t_room *room = phil->room;
	gettimeofday(&phil->t1, NULL);
	// printf("PHIL %d, %ld\n", phil->n, phil->t1.tv_sec);
	
	while ((phil->n_e < room->n_must_eat && room->n_must_eat != -1)	|| room->n_must_eat == -1)
	{
		do_get(phil, room);
		
		do_eat(phil, phil->room);
		
		do_drop(phil, phil->room);
		
		do_sleep(phil, phil->room);
		
		if (phil->state == DIE)
			return (NULL);
		do_think(phil, phil->room);
	}
	
	return (NULL);
}
void	printer(t_phil *phil)
{
	t_room	*room;

	room = (t_room *)phil->room;
	
	pthread_mutex_lock(room->mu_print);
	gettimeofday(&room->t2, NULL);
	ft_putnbr_fd(((room->t2.tv_usec / 1000) + room->t2.tv_sec * 1000) - ((room->t1.tv_usec / 1000) + room->t1.tv_sec * 1000), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(phil->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(phil->status, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(room->mu_print);
}

int		some_dead(t_room *room)
{
	int i;

	i = 0;
	while (i < room->n_phils)
	{
		if (room->phils[i].state == DIE)
			return (1);
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
		while (i < room->n_phils)
		{
			gettimeofday(&room->phils[i].t2, NULL);
			if ((((unsigned long long)(((room->phils[i].t2.tv_usec / 1000)
			+ room->phils[i].t2.tv_sec * 1000)
			- ((room->phils[i].t1.tv_usec / 1000)
			+ room->phils[i].t1.tv_sec * 1000))
			> room->t_die / 1000) && room->phils[i].n_e < room->n_must_eat
				&& room->n_must_eat != -1)
				|| (((unsigned long long)(((room->phils[i].t2.tv_usec / 1000) + room->phils[i].t2.tv_sec * 1000)
				- ((room->phils[i].t1.tv_usec / 1000) + room->phils[i].t1.tv_sec * 1000))
				>= (room->t_die / 1000)) && room->n_must_eat == -1))
			{
				unsigned long long b = (room->phils[i].t2.tv_usec / 1000) + (room->phils[i].t2.tv_sec * 1000);
				unsigned long long a = (room->phils[i].t1.tv_usec / 1000) + (room->phils[i].t1.tv_sec * 1000);
				printf("%llu - %llu = %llu | %llu\n",b, a, b - a, room->t_die / 1000);
				room->phils[i].state = DIE;
				room->phils[i].status = " is died";
				printer(&room->phils[i]);
				exit(0);
			}
			i++;
		}
	}

	return (0);
}

// 1 641 736 519 772
// 1 641 736 519 546=226
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

	// if (ac == 5)
	// 	write(1, "4 agrs\n", 8);
	// else
	// 	write(1, "5 args\n", 8);
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
		room->phils[i].id = i + 1;
		room->phils[i].ind = i;
		room->phils[i].room = room;
		room->phils[i].l_f = room->phils[i].ind;
		room->phils[i].r_f = room->phils[i].ind - 1;
		if (i == 0)
			room->phils[i].r_f = room->n_phils - 1;
		room->forks[i].room = room;
		room->forks[i].use = 0;
		pthread_mutex_init(&room->forks[i].mu, NULL);
		i++;
	}
	room->mu_print = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(room->mu_print, NULL);
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
	while (room->phils[room->n_phils - 1].t1.tv_sec == 0)
	{
		usleep(21);
	}
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
