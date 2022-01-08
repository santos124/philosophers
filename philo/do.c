#include "philo.h"

int do_get(t_phil *phil)
{

	pthread_create(&phil->tr_l, NULL, get_fork, phil);
	pthread_create(&phil->tr_r, NULL, get_fork, phil);
	pthread_join(phil->tr_l, NULL);
	pthread_join(phil->tr_r, NULL);
	printf("Philosoph %d is GET FORK\n", phil->n);
	return 0;
}

int do_drop(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;
	printf("Philosoph %d is DROP FORK\n", phil->n);
	return 0;
}

int do_think(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;
	printf("Philosoph %d is THINK\n", phil->n);
	return 0;
}

int		do_eat(t_phil *phil, t_room *room)
{
	(void)phil;
	(void)room;
	printf("Philosoph %d is EAT\n", phil->n);
	return 0;
}

int do_sleep(t_phil *phil, t_room *room)
{

	(void)phil;
	(void)room;
	printf("Philosoph %d is SLEEP\n", phil->n);
	return 0;
}
