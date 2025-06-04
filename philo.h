/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:32:44 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/04 13:46:24 by khhihi           ###   ########.fr       */
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
#include <stdint.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int                 id;
    long long           last_meal;
    int                 meals_eaten;
    int                 two_forks;
    bool                has_fork;
    pthread_t		    routine;
    pthread_t			thread;
    t_data              *data;
    pthread_mutex_t		meal_mutex;

}   t_philo;

typedef struct s_data
{
    int number_philos;
    int die_time;
    int eat_time;
    int sleep_time;
    int dead;
    int		must_eat_count;
    long long           start;
    pthread_mutex_t     *forks;
    pthread_mutex_t		meal_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
    t_philo             *philos;
}       t_data;

int             check_args(char **av);
int             init(t_data *data, char **av);
void	        free_data(t_data *data);
int	            start_simulation(t_data *data);
void	        *the_monitor(void *arg);
int             check_is_dead(t_philo *philo);
void            print_status(t_philo *philo, char *status);
void            *philo_routine(void *arg);
void	        smart_sleep(t_philo *philo, long long duration);
int	            ft_atoi(const char *str);
long long	    get_curr_time_ms(void);
