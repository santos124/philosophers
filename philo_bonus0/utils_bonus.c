#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	get_time(void)
{
	struct timeval	actual;

	gettimeofday(&actual, NULL);
	return (actual.tv_sec * 1000 + actual.tv_usec / 1000);
}

static long long	get_delta_time(struct timeval t1, struct timeval t2)
{
	return ((long long)((t2.tv_sec * 1000 + (t2.tv_usec / 1000))
		- (t1.tv_sec * 1000 + (t1.tv_usec / 1000))));
}

void	milisleep(long long ms)
{
	struct timeval	t1;
	struct timeval	t2;

	gettimeofday(&t1, NULL);
	gettimeofday(&t2, NULL);
	while (get_delta_time(t1, t2) < (long long)ms)
	{
		usleep(200);
		gettimeofday(&t2, NULL);
	}
}


int	ft_atoi(char *str)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 0;
	c = 1;
	if (str[a] == '\0')
		return (0);
	while (str[a] == '\n' || str[a] == '\r' || str[a] == '\t'
		|| str[a] == '\v' || str[a] == ' ' || str[a] == '\f')
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			c = -c;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
		b = (b * 10) + (str[a++] - 48);
	return (b * c);
}
