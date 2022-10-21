/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:10:23 by adouay            #+#    #+#             */
/*   Updated: 2022/10/21 18:45:41 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	did_philo_is_stoped(t_philo *philo)
{
	int	bol;

	pthread_mutex_lock(&philo->data->dead_checker);
	bol = 0;
	if (philo->data->stop)
		bol = 1;
	pthread_mutex_unlock(&philo->data->dead_checker);
	return (bol);
}

int	did_philo_have_to_stop(t_data *data)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].meal_lock);
		if (get_timestamp(data) - data->philo[i].last_meal >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo[i].meal_lock);
			print(&data->philo[i], 5);
			return (1);
		}
		if (data->philo[i].nbr_of_meal == data->nbr_of_eat
			&& data->nbr_of_eat != -1)
			counter++;
		pthread_mutex_unlock(&data->philo[i].meal_lock);
		i++;
	}
	if (counter == data->nbr_of_philo)
		return (1);
	return (0);
}

void	*dead_checker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (did_philo_have_to_stop(data))
		{
			pthread_mutex_lock(&data->dead_checker);
			data->stop = 1;
			pthread_mutex_unlock(&data->dead_checker);
			return (NULL);
		}
		usleep(200);
	}
}
