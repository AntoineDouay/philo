/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:05:12 by adouay            #+#    #+#             */
/*   Updated: 2022/10/21 21:41:05 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_well(t_philo *philo, int time)
{
	int	goal;

	goal = get_timestamp(philo->data) + time;
	while (get_timestamp(philo->data) < goal)
	{
		if (did_philo_is_stoped(philo))
			break ;
		usleep(100);
	}
}
/*
void	think(t_philo *philo)
{
	print(philo, 4);
	usleep(500);
}
*/
void	eat_solo(t_philo *philo)
{
	print(philo, 1);
	sleep_well(philo, philo->data->time_to_die + 1000);
}

void	rev_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print(philo, 1);
	pthread_mutex_lock(philo->r_fork);
	print(philo, 1);
	pthread_mutex_lock(&philo->meal_lock);
	print(philo, 2);
	philo->last_meal = get_timestamp(philo->data);
	philo->nbr_of_meal++;
	pthread_mutex_unlock(&philo->meal_lock);
	sleep_well(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	print(philo, 3);
	sleep_well(philo, philo->data->time_to_sleep);
	print(philo, 4);
	usleep(500);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print(philo, 1);
	pthread_mutex_lock(philo->l_fork);
	print(philo, 1);
	pthread_mutex_lock(&philo->meal_lock);
	print(philo, 2);
	philo->last_meal = get_timestamp(philo->data);
	philo->nbr_of_meal++;
	pthread_mutex_unlock(&philo->meal_lock);
	sleep_well(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print(philo, 3);
	sleep_well(philo, philo->data->time_to_sleep);
	print(philo, 4);
	usleep(500);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_of_philo == 1)
		eat_solo(philo);
	if ((philo->id - 1) % 2)
		usleep(8000);
	while (!did_philo_is_stoped(philo))
	{
		if ((philo->id - 1) % 2 == 0)
			eat(philo);
		else
			rev_eat(philo);
	}
	return (NULL);
}
