/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:31:40 by wadina            #+#    #+#             */
/*   Updated: 2022/01/05 13:31:43 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include	<string.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/time.h>
# include	<pthread.h>

//time
typedef struct timeval t_time;

//phil
typedef struct s_phil {
	t_time		t1;
	t_time		t2;
	void		*room;
	int			n;
	int			n_e;
	pthread_t	tr;
}				t_phil;

//fork
typedef struct s_fork {
	pthread_mutex_t	mu;
	int				n;
}				t_fork;

//room
typedef struct s_room {
	t_phil	*phils;
	t_fork	*forks;
	int		n_phils;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_must_eat;
}				t_room;


int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);

#endif
