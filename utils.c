/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:50:30 by adouay            #+#    #+#             */
/*   Updated: 2022/10/21 19:41:49 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timestamp(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000)
		- (data->start_time.tv_sec * 1000 + data->start_time.tv_usec / 1000));
}

void	print(t_philo *philo, int type)
{
	int	time;

	time = get_timestamp(philo->data);
	pthread_mutex_lock(&philo->data->print);
	if (!did_philo_is_stoped(philo))
	{
		if (type == 1)
			printf ("%i  %i has taken a fork\n", time, philo->id);
		if (type == 2)
			printf ("%i  %i is eating\n", time, philo->id);
		if (type == 3)
			printf ("%i  %i is sleeping\n", time, philo->id);
		if (type == 4)
			printf ("%i  %i is thinking\n", time, philo->id);
	}
	if (type == 5)
		printf ("%i  %i died\nlast meal was at %i\n", time,
			philo->id, philo->last_meal);
	pthread_mutex_unlock(&philo->data->print);
}

int	check_int(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char *argv[])
{
	long int	tmp;
	int			i;

	if (argc != 5 && argc != 6)
		return (1);
	if (check_int(argv))
		return (1);
	i = 1;
	while (argv[i])
	{
		tmp = ft_atoi(argv[i]);
		if (tmp < INT_MIN || tmp > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

long int	ft_atoi(const char *nptr)
{
	int			sign;
	long int	res;

	sign = 1;
	res = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
	nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr++ == '-')
			sign = -sign;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	if ((sign * res) <= INT_MAX && (sign * res) >= INT_MIN)
		return (sign * res);
	else
		return (LONG_MAX);
}
