#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>

struct	s_room;

typedef struct s_phil
{
	int					id;
	struct s_room		*room;
	long long			eat_last;
	pid_t				p_id;
	int					is_eating;
	int					count;
	pthread_t			tr;
}				t_phil;

typedef struct s_room
{
	
	sem_t					*forks;
	sem_t					*printer;
	sem_t					*sema3;
	t_phil					*phil;
	long long				t_die;
	long long				t_sleep;
	long long				t_eat;
	long long				start;
	pid_t					p_id;
	int						n_must_eat;
	int						died;
	int						n_phils;
	int						one;

}				t_room;

int				ft_isdigit(int c);
long long		get_time(void);
void			milisleep(long long time);
int				ft_atoi(char *str);
t_phil			*phil_info(t_room *room);
t_room			*philo_args(int ac, char **av, t_room *room);
t_room			*room_init(int ac, char **av);
int				ft_death(t_phil *phil);
void			*sentinel(void *ptr);
void			eat(t_phil *phil);
int				liberator(t_room *room, int code);
int				error_checker(char **av);
void				processes(void *ptr);

#endif
