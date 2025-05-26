/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:47:13 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/25 16:26:45 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int init_data(t_data *data, char **av)
{
    int i = 0;
    write(1, "here===\n", 9);
    memset(data, 0, sizeof(t_data));
    data->number_philos = ft_atoi(av[1]);
    data->die_time = ft_atoi(av[2]);
    data->eat_time = ft_atoi(av[3]);
    data->sleep_time = ft_atoi(av[4]);
    if(av[5])
        data->meals = ft_atoi(av[5]);
    data->dead = 0;
    data->start = get_time();
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philos);
    if(!data->forks)
        return (0);
    while(i < data->number_philos)
    {
        if(pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (0);
        i++;
    }
    return(1);
}

int    init(t_data *data, char **av)
{
    if (!init_data(data, av))
        return (1);
    return (0);
}
int check_args(char **av)
{
    if (ft_atoi(av[1]) < 1)
        return (printf("Enter a valid philo number"),1);
    if (ft_atoi(av[2]) < 1)
        return (printf("Enter a valid time to die number"), 1);
    if (ft_atoi(av[3]) < 1)
        return (printf("Enter a valid time to eat number"), 1);
    if (ft_atoi(av[4]) < 1)
        return (printf("Enter a valid time to sleep number"), 1);;
    if (ft_atoi(av[5]) < 1)
        return (printf("Enter a valid times to eat number"), 1);
    write(1, "here===\n", 9);
    return (0);
}