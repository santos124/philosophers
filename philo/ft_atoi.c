/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:08:07 by wadina            #+#    #+#             */
/*   Updated: 2021/05/11 20:41:37 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

static int	ft_ok(char c)
{
	if (c == 9 || c == 10 || c == 11)
		return (2);
	else if (c == 12 || c == 13 || c == 32)
		return (2);
	else if (ft_isdigit(c))
		return (1);
	else if (c == '-' || c == '+')
		return (3);
	else
		return (5);
}

static long	ft_mult(const char *str, int i, long num, long sign)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((num * sign) < -2147483648)
			return (0);
		else if ((num * sign) > 2147483647)
			return (-1);
		else
			num = num * 10 + str[i] - '0';
		if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
			break ;
		i++;
	}
	return (num * sign);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	long	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] && ft_ok(str[i]) < 4)
	{
		if (ft_ok(str[i]) == 3 && ft_ok(str[i + 1]) == 1)
			if (str[i] == '-')
				sign = -1;
		if (ft_ok(str[i]) == 3 && ft_ok(str[i + 1]) != 1)
			break ;
		if (ft_isdigit(str[i]))
		{
			num = ft_mult(str, i, num, sign);
			break ;
		}
		if (ft_ok(str[i]) == 2 && ft_ok(str[i + 1]) == 3)
			if (ft_ok(str[i + 2]) != 1)
				break ;
		i++;
	}
	return (num);
}
