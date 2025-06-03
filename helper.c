/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:54:23 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/02 13:24:35 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec * 1000LL) + ((long long)tv.tv_usec / 1000LL));
}

void	smart_sleep(t_philo *philo, long long duration)
{
	long long	start_time;

	start_time = get_current_time_ms();
	while ((get_current_time_ms() - start_time < duration)
		&& !check_is_dead(philo))
		usleep(50);
}

int	check_is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	is_dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (is_dead);
}

void print_status(t_philo *philo, char *status)
{
	long long time;

	time = get_time() - philo->data->start;
	if (check_is_dead(philo))
		return ;
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

