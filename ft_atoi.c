/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:49:57 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/09 13:30:37 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	r;

	int (i), (s);
	i = 0;
	s = 1;
	r = 0;
	if (!str)
		return (0);
	while ((str[i]) && (str[i] <= 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while ((str[i]) && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i++] - 48);
		if (r < 0 || r > INT_MAX)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (s * r);
}
