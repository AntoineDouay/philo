/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:44:36 by adouay            #+#    #+#             */
/*   Updated: 2022/10/19 19:12:59 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data data;
	
	if (check_args(argc, argv))
		return (0);
	init_data(&data, argc, argv);
	init_fork(&data);
	init_philo(&data);
	pthread_create(&data.checker, NULL, &dead_checker, &data);
	int i = 0;
	pthread_join(data.checker, NULL);
	while (i < data.nbr_of_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data.nbr_of_philo)
	{
		pthread_mutex_destroy(&data.fork[i].fork_mutex);
		pthread_mutex_destroy(&data.philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data.dead_checker);
	pthread_mutex_destroy(&data.print);
	free (data.fork);
	free (data.philo);
	return (0);
}