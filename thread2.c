/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:10:23 by adouay            #+#    #+#             */
/*   Updated: 2022/10/19 17:46:30 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_back_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork_mutex);
	fork->state = 0;
	pthread_mutex_unlock(&fork->fork_mutex);
}

int	try_fork(t_fork *fork)
{
	int	bol;

	bol = 0;
	pthread_mutex_lock(&fork->fork_mutex);
	if (!fork->state)
	{
		fork->state = 1;
		bol = 1;
	}
	pthread_mutex_unlock(&fork->fork_mutex);
	return (bol);
}

int	did_philo_is_stoped(t_philo *philo)
{
	int	bol;

	bol = 0;
	pthread_mutex_lock(&philo->data->dead_checker);
	if (!philo->data->stop)
		bol = 1;
	pthread_mutex_unlock(&philo->data->dead_checker);
	return (bol);
}
