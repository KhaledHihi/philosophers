/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:54:23 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/28 17:23:04 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void print_status(t_philo *philo, char *status)
{
	long long time;

	time = get_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n",time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
struct timeval get_curr_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	free(data->forks);
	free(data->philos);
	// free(data);
}

