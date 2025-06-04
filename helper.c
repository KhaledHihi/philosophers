/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:54:23 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/04 12:55:00 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_curr_time_ms(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return ((time_value.tv_sec * 1000LL) + (time_value.tv_usec / 1000));
}

void	smart_sleep(t_philo *philo, long long duration)
{
	long long	start_time;

	start_time = get_curr_time_ms();
	while ((get_curr_time_ms() - start_time < duration)
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
    long long		timestamp;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (check_is_dead(philo))
    {
        pthread_mutex_unlock(&philo->data->print_mutex);
        return ;
    }
    timestamp = get_curr_time_ms() - philo->data->start;
    printf("%lld %d %s\n", timestamp, philo->id, status);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void	free_data(t_data *data)
{
    int	i;

    if (!data)
        return ;
    i = 0;
    while (i < data->number_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].meal_mutex);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
    if (data->forks)
        free(data->forks);
    if (data->philos)
        free(data->philos);
}

