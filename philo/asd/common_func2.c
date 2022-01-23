#include "philo.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < -9)
		ft_putnbr_fd((n - n % 10) / 10, fd);
	if (n > 9)
		ft_putnbr_fd((n - n % 10) / 10, fd);
	if (n < 0 && n >= -9)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = n + 2000000000;
			n = -n;
		}	
		else
		{
			n = -n;
		}
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			ft_putchar_fd(s[i++], fd);
		}
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

