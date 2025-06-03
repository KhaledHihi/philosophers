/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:32:44 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/03 13:39:26 by khhihi           ###   ########.fr       */
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
#include <stdint.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int                 id;
    struct timeval      last_meal;
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
struct          timeval get_curr_time(void);
void	        free_data(t_data *data);
int	            start_simulation(t_data *data);
void	        *the_monitor(void *arg);
long long       get_time(void);
struct timeval  get_curr_time(void);
int             check_is_dead(t_philo *philo);
void            print_status(t_philo *philo, char *status);
void            *philo_routine(void *arg);
void	        smart_sleep(t_philo *philo, long long duration);
long long	    get_current_time_ms(void);
int	            ft_atoi(const char *str);
