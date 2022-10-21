/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:44:36 by adouay            #+#    #+#             */
/*   Updated: 2022/10/21 21:31:58 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_philo(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->checker, NULL);
	while (i < data->nbr_of_philo)
		pthread_join(data->philo[i++].thread, NULL);
	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->dead_checker);
	pthread_mutex_destroy(&data->print);
	free (data->fork);
	free (data->philo);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	i = 0;
	if (check_args(argc, argv))
		return (0);
	if(init_data(&data, argc, argv))
		return (write(2, "ERROR INIT\n", 11));
	if (data.nbr_of_eat == -2)
		return (0);
	if (init_fork(&data))
		return (write(2, "ERROR INIT\n", 11));
	if (init_philo(&data))
		return (write(2, "ERROR INIT\n", 11));
	if (pthread_create(&data.checker, NULL, &dead_checker, &data))
		return (write(2, "ERROR INIT\n", 11));
	end_philo(&data);
	return (0);
}
