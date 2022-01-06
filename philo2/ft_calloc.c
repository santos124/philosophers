/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:16:48 by wadina            #+#    #+#             */
/*   Updated: 2021/05/06 20:16:50 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	int		i;

	i = 0;
	arr = malloc(count * size);
	if (arr == NULL)
		return (arr);
	while (i < (int)(count * size))
	{
		((char *)arr)[i++] = 0;
	}
	return (arr);
}
