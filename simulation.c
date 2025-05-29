/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:00:28 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/29 15:59:07 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void 	pick_fork(t_philo *philo)
{
	int left_fork;
	int right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->number_philos;
	if (philo->id % 2 != 0)
		usleep(2000);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		pthread_mutex_lock(&philo->data->forks[left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->forks[right_fork]);
	}
}

void	release_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->number_philos;
	if (philo->id % 2 != 0)
		usleep(100);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
	}
}

void	*philo_routine(t_data *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_is_dead(philo))
			return (NULL);
		print_status(philo, "is thinking");
		pick_fork(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_curr_time();
		pthread_mutex_unlock(&philo->meal_mutex);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		release_forks(philo);
		if (check_is_dead(philo))
			return (NULL);
		print_status(philo, "is sleeping");
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i = 0;
	// pthread_t monitor;

	while (i < data->number_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine(data), &data->philos[i]) != 0)
			return (write(2, "Error: Failed to create philosopher thread\n", 44), 1);
		i++;
	}
	// if (pthread_create(&monitor, 0 ,the_monitor, data) != 0)
	// 	return (write(2, "Error: Failed to create monitor thread\n", 40), 1);
	i = 0;
	while (i < data->number_philos)
		pthread_join(data->philos[i++].thread, NULL);
	// pthread_join(&monitor, NULL);
	return (free_data(data), 0);
}
