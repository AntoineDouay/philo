/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:42:53 by adouay            #+#    #+#             */
/*   Updated: 2022/10/19 21:28:41 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H 
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>

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
	struct timeval 	start_time;
	struct s_fork	*fork;
	struct s_philo	*philo;
}	t_data;

typedef struct s_fork{
	int				state;
	pthread_mutex_t fork_mutex;
}	t_fork;

typedef struct s_philo{
	int					id;
	int					last_meal;
	int					nbr_of_meal;
	pthread_mutex_t		meal_lock;
	struct s_fork		*l_fork;
	struct s_fork		*r_fork;
	pthread_t 			thread;
	t_data				*data;
}	t_philo;

void		init_philo(t_data *data);
void    	init_fork(t_data *data);
void		init_data(t_data *data, int argc, char *argv[]);

void 		eat(t_philo *philo);
void		*routine(void *arg);

int			did_philo_have_to_stop(t_data *data);
void		*dead_checker(void *arg);

void		put_back_fork(t_fork *fork);
int			try_fork(t_fork *fork);
int			did_philo_is_stoped(t_philo *philo);

void		sleep_well(t_philo *philo, int time);
int 		get_timestamp(t_data *data);
void		print(t_philo *philo, int type);
long int	ft_atoi(const char *nptr);
int 		check_args(int argc, char *argv[]);

#endif