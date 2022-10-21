/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:37:18 by adouay            #+#    #+#             */
/*   Updated: 2022/10/21 21:35:20 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].nbr_of_meal = 0;
		if (pthread_mutex_init(&data->philo[i].meal_lock, NULL))
			return (1);
		if (i == 0)
			data->philo[i].l_fork = &data->fork[data->nbr_of_philo - 1];
		else
			data->philo[i].l_fork = &data->fork[i - 1];
		data->philo[i].r_fork = &data->fork[i];
		data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread,
				NULL, &routine, &data->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (1);
		i++;
	}
	return(0);
}

int	init_data(t_data *data, int argc, char *argv[])
{
	data->nbr_of_eat = -1;
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->stop = 0;
	if (argc == 6)
		data->nbr_of_eat = ft_atoi(argv[5]);
	if (data->nbr_of_eat == 0)
	{
		data->nbr_of_eat = -2;
		return (0);
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead_checker, NULL))
		return (1);
	gettimeofday(&data->start_time, NULL);
	data->philo = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philo)
		return (1);
	data->fork = malloc (sizeof(pthread_mutex_t) * data->nbr_of_philo);
	if (!data->fork)
	{
		free(data->philo);
		return (1);
	}
	return (0);
}
