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
# define THINK 1
# define GET_FORK 2
# define EAT 3
# define SLEEP 4
# define DIE 5
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
	t_time			dinner;
	t_time			check;

	struct s_room	*room;
	int				state;
	char			*status;
	int				id;
	int				ind;
	int				n_e;
	int				l_f;
	int				r_f;
	pthread_t		tr;
	pthread_mutex_t	mu;
	int				can_eat;
}				t_phil;

//fork
typedef struct s_fork {
	void			*room;
	pthread_t		tr;
	pthread_mutex_t	mu;
	int				n;
	int				use;
}				t_fork;

//room
typedef struct	s_room {
	t_phil			*phils;
	t_fork			*forks;
	pthread_t		palach;
	pthread_t		serve;
	pthread_t		pri;
	
	pthread_mutex_t	mu_print;
	t_time			t1;
	t_time			t2;
	int				n_phils;
	unsigned long long			t_die;
	unsigned long long			t_eat;
	unsigned long long			t_sleep;
	int				n_must_eat;
	int				death;
	
}				t_room;


int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
int		do_get(t_phil *phil, t_room *room);
int		do_drop(t_phil *phil, t_room *room);
int		do_eat(t_phil *phil, t_room *room);
int		do_think(t_phil *phil, t_room *room);
int		do_sleep(t_phil *phil, t_room *room);
void 	get_fork(t_phil *phil);
void	*get_fork_r(void *ptr);
int		drop_fork(int f, t_phil *phil, t_room *room);
void	*printer(void *ptr);
unsigned long long get_time(t_time t1, t_time t2);


#endif
