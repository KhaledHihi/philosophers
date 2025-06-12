/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_monitor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:11:29 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/11 15:46:28 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int i)
{
	long long	last_meal_time_ms;
	long long	current_time_ms;
	long long	timestamp;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	last_meal_time_ms = (data->philos[i].last_meal);
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	current_time_ms = get_curr_time_ms();
	if ((current_time_ms - last_meal_time_ms) >= data->die_time)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->death_mutex);
		data->dead = 1;
		timestamp = current_time_ms - data->start;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n", timestamp, data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

int	check_meals(t_data *data)
{
	int (i), (meals);
	meals = 0;
	i = 0;
	if (data->must_eat_count == -1)
		return (0);
	while (i < data->number_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			meals++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	if (data->number_philos == meals)
	{
		pthread_mutex_lock(&data->print_mutex);
		pthread_mutex_lock(&data->death_mutex);
		data->dead = 1;
		printf("all philosophers have finished their meals\n");
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

void	*the_monitor(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		if (check_meals(data))
			return (NULL);
		while (i < data->number_philos)
		{
			if (check_death(data, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
