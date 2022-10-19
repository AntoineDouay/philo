/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:37:18 by adouay            #+#    #+#             */
/*   Updated: 2022/10/19 21:05:44 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		data->philo[i].id = i + 1;
        data->philo[i].last_meal = 0;
        data->philo[i].nbr_of_meal = 0;
        pthread_mutex_init(&data->philo[i].meal_lock, NULL);
		if (i == 0)
			data->philo[i].l_fork = &data->fork[data->nbr_of_philo - 1];
		else
			data->philo[i].l_fork = &data->fork[i - 1];
        data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]))
			return ; // ERROR
		i++;
	}
}

void    init_fork(t_data *data)
{
    int i;
    
    i = 0;
    while(i < data->nbr_of_philo)
    {
        data->philo[i].r_fork = &data->fork[i];
        data->fork[i].state = 0;
        if (pthread_mutex_init(&data->fork[i].fork_mutex, NULL))
			return ; // ERROR
        i++;
    }
}

void	init_data(t_data *data, int argc, char *argv[])
{
    data->nbr_of_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->stop = 1;
    if (argc == 6)
        data->nbr_of_eat = ft_atoi(argv[5]);
    else
        data->nbr_of_eat = -1;
    pthread_mutex_init(&data->print, NULL);
    pthread_mutex_init(&data->dead_checker, NULL);
	gettimeofday(&data->start_time, NULL);
	data->philo = malloc(sizeof(t_philo) * data->nbr_of_philo);
	data->fork = malloc (sizeof(t_fork) * data->nbr_of_philo);
}