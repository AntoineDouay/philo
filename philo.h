/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:42:53 by adouay            #+#    #+#             */
/*   Updated: 2022/10/21 21:11:47 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_data{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_eat;
	int				stop;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_checker;
	pthread_t		checker;
	struct timeval	start_time;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo{
	int					id;
	int					last_meal;
	int					nbr_of_meal;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread;
	t_data				*data;
}	t_philo;

int		init_philo(t_data *data);
int		init_fork(t_data *data);
int		init_data(t_data *data, int argc, char *argv[]);

void		eat(t_philo *philo);
void		think(t_philo *philo);
void		*routine(void *arg);

int			did_philo_have_to_stop(t_data *data);
void		*dead_checker(void *arg);

int			did_philo_is_stoped(t_philo *philo);

void		sleep_well(t_philo *philo, int time);
int			get_timestamp(t_data *data);
void		print(t_philo *philo, int type);
long int	ft_atoi(const char *nptr);
int			check_args(int argc, char *argv[]);

#endif