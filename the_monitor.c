/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_monitor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:11:29 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/03 13:36:14 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
static int check_death(t_data *data, int i, struct timeval *current_time)
{
	long long time_since_last_meal;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	time_since_last_meal = (current_time->tv_sec * 1000 + current_time->tv_usec / 1000)
		- (data->philos[i].last_meal.tv_sec * 1000 + data->philos[i].last_meal.tv_usec / 1000);
	pthread_mutex_unlock(&data->philos[i].meal_mutex);

	if (time_since_last_meal > data->die_time)
	{
		pthread_mutex_lock(&data->print_mutex);
		pthread_mutex_lock(&data->death_mutex);
		data->dead = 1;
		printf("Philosopher %d has died.\n", i + 1);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}
int	check_meals(t_data *data)
{
	int i;
	int meals;

	meals = 0;
	i = 0;
	while (i < data->number_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			meals++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	if(data->number_philos == meals)
	{
		pthread_mutex_lock(&data->print_mutex);
		pthread_mutex_lock(&data->death_mutex);
		data->dead = 1;
		printf("All philosophers have eaten enough meals.\n");
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}
void	*the_monitor(void *arg)
{
	(void)arg;
	int i;
	struct timeval	current_time;
	t_data	*data;
	(void)i;
	data = (t_data *)arg;
	while(1)
	{
		i = 0;
		if (!check_meals(data))
		return (NULL);
		while (i < data->number_philos)
		{
			gettimeofday(&current_time, NULL);
			if (check_death(data, i, &current_time))
				return (NULL);
			i++;
		}
		if (data->number_philos % 2 != 0)
			usleep(200);
		
	}
	return (NULL);
}
