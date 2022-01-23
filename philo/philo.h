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
	t_time			t1;
	t_time			t2;
	t_time			tf1;
	t_time			tf2;
	t_time			t_fork1;
	t_time			t_fork2;

	void			*room;
	pthread_t		tr_l;
	pthread_t		tr_r;
	pthread_t		t_print;
	int				state;
	char			*status;
	int				id;
	int				ind;
	int				n_e;
	int				l_f;
	int				r_f;
	pthread_t		tr;
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
	pthread_mutex_t	mu_print;
	t_time			t1;
	t_time			t2;
	int				n_phils;
	uint64_t			t_die;
	uint64_t			t_eat;
	uint64_t			t_sleep;
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
void 	*get_fork(void *ptr);
void	*get_fork_r(void *ptr);
int		drop_fork(int f, t_phil *phil, t_room *room);
void	*printer(t_phil *phil);
uint64_t get_time(t_time t1, t_time t2);


#endif
