/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:32:44 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/25 16:58:22 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_philo
{
    int id;
    int last_meal;
    int two_forks;
    pthread_t		routine;
    
}   t_philo;

typedef struct s_data
{
    int number_philos;
    int die_time;
    int eat_time;
    int sleep_time;
    int meals;
    int dead;
    long long start;
    pthread_mutex_t *forks;
}       t_data;

int     check_args(char **av);
int     init(t_data *data, char **av);