#include "philo.h"

void	*get_fork(void *ptr)
{
	t_phil *phil;
	t_room *room;

	phil = (t_phil *)ptr; 
	room = (t_room *)phil->room;

	return 0;
}

int drop_fork(int f, t_phil *phil, t_room *room)
{
	(void)f;
	(void)phil;
	(void)room;
	return 0;
}
