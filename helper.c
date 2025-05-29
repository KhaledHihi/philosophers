/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:54:23 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/29 15:58:51 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(2, "Error: Mutex initialization failed\n", 35);
			return (1);
		}
		i++;
	}
	return (0);
}

int check_is_dead(t_philo *philo)
{
	int dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (dead);
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

