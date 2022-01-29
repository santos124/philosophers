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

typedef struct timeval	t_time;

typedef struct s_phil {
	t_time				dinner;
	struct s_room		*room;
	int					state;
	char				*status;
	int					id;
	int					ind;
	int					n_e;
	int					f_f;
	int					s_f;
	pthread_t			tr;
	int					can_eat;
}				t_phil;

typedef struct s_room {
	t_phil				*phils;
	pthread_mutex_t		*f_mu;
	pthread_mutex_t		mu_print;
	t_time				t1;
	t_time				t2;
	pthread_t			sentinel_t;
	t_time				death_t;
	int					n_phils;
	long long			t_die;
	long long			t_eat;
	long long			t_sleep;
	int					n_must_eat;
	int					death;
	int					start;
}				t_room;

int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
int			ft_isdigit(int c);
void		ft_putchar_fd(char c, int fd);
void		ft_printer(t_phil *phil, t_room *room);
long long	get_time(t_time t1, t_time t2);
void		milisleep(int ms);
void		*f_phil(void *p);
void		ft_printer(t_phil *phil, t_room *room);
void		*ft_sentinel(void *ptr);
void		ft_death(t_room *room);
int			ft_hungry(t_room *room);
t_room		*init_room(int ac, char **av);

#endif
