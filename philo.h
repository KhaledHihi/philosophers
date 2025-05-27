/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:32:44 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/27 13:39:25 by khhihi           ###   ########.fr       */
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
# include <stdbool.h>
# include "libft/libft.h"

typedef struct s_data t_data;

typedef struct s_philo
{
    int                 id;
    struct timeval      last_meal;
    int                 meals_eaten;
    int                 two_forks;
    bool                has_fork;
    pthread_t		    routine;
    t_data              *data;
    pthread_mutex_t		meal_mutex;

}   t_philo;

typedef struct s_data
{
    int number_philos;
    int die_time;
    int eat_time;
    int sleep_time;
    int meals;
    int dead;
    long long           start;
    pthread_mutex_t     *forks;
    pthread_mutex_t		meal_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
    t_philo             *philos;
}       t_data;

int     check_args(char **av);
int     init(t_data *data, char **av);
struct  timeval get_curr_time(void);
void	free_data(t_data *data);
