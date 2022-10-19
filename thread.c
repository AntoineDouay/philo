/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:05:12 by adouay            #+#    #+#             */
/*   Updated: 2022/10/19 21:31:50 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		did_philo_have_to_stop(t_data *data)
{
	int	i;
	int counter; 

	i = 0;
	counter = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].meal_lock);
		if (get_timestamp(data) - data->philo[i].last_meal >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo[i].meal_lock);
			print(&data->philo[i], 4);
			return (1);
		}
		if (data->philo[i].nbr_of_meal == data->nbr_of_eat && data->nbr_of_eat != -1)
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
	while(1)
	{
		if(did_philo_have_to_stop(data))
		{
			pthread_mutex_lock(&data->dead_checker);
			data->stop = 0;
			pthread_mutex_unlock(&data->dead_checker);
			return (NULL);
		}
	}
}

void  eat_solo(t_philo *philo)
{
    try_fork(philo->l_fork);
    print(philo, 1);
    sleep_well(philo, philo->data->time_to_die + 1000);
}

void eat(t_philo *philo)
{
	print(philo, 1);
	print(philo, 1);
	print(philo, 2);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_timestamp(philo->data);
	philo->nbr_of_meal++;
	pthread_mutex_unlock(&philo->meal_lock);
    usleep(philo->data->time_to_eat * 1000);
	//sleep_well(philo, philo->data->time_to_eat);
	put_back_fork(philo->l_fork);
	put_back_fork(philo->r_fork);
	pthread_mutex_lock(&philo->data->dead_checker);	
	if (philo->data->stop)
		print(philo, 3);
	pthread_mutex_unlock(&philo->data->dead_checker);
	//sleep_well(philo, philo->data->time_to_sleep);
    usleep(philo->data->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
    if (philo->data->nbr_of_philo == 1)
        eat_solo(philo);
	while(1)
	{
		pthread_mutex_lock(&philo->data->dead_checker);
		if(philo->data->stop)
        {
			pthread_mutex_unlock(&philo->data->dead_checker);
			if (try_fork(philo->l_fork))
				if (try_fork(philo->r_fork))
					eat(philo);
				else
					put_back_fork(philo->l_fork);
        }
        else
		{
			pthread_mutex_unlock(&philo->data->dead_checker);
			return (NULL);	
		}
	}
}