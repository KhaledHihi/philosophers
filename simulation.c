/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:00:28 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/27 15:40:11 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_create(&monitor)
}
