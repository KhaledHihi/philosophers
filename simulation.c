/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:00:28 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/28 15:47:28 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	*philo_routine(t_data *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		print_status(philo, "is thinking");
	}
}
int	start_simulation(t_data *data)
{
	int	i = 0;
	pthread_t monitor;

	while (i < data->number_philos)
	{
		if (pthread_create(data->philos[i].thread, 0, philo_routine(data), &data->philos[i]) != 0)
			return (write(2, "Error: Failed to create philosopher thread\n", 44), 1);
		i++;
	}
	if (pthread_create(&monitor, 0 ,the_monitor, data) != 0)
		return (write(2, "Error: Failed to create monitor thread\n", 40), 1);
	i = 0;
	while (i < data->number_philos)
		pthread_join(data->philos[i++].thread, NULL);
	pthread_join(&monitor, NULL);
	return (free_data(data), 0);
}
