/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:31:59 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/03 17:52:40 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac != 5 && ac != 6)
        return (printf("error"), 1);
    if (check_args(av) || init(&data, av))
        return (1);
    if (data.number_philos == 1)
    {
        printf("0 1 is thinking\n");
        usleep(data.die_time * 1000);
        printf("%d 1 died\n", data.die_time);
        return (free_data(&data), 0);
    }
    start_simulation(&data);
}
