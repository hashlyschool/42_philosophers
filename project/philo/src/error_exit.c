/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:23:36 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 14:15:18 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	if error
		output message
		write error to data->error
*/
int	ft_set_error(t_data *data, int error, char *message)
{
	pthread_mutex_lock(&data->error_m);
	if (error && !data->error)
	{
		data->error = error;
		if (message)
			printf("%s", message);
	}
	pthread_mutex_unlock(&data->error_m);
	return (0);
}

int	ft_check_error(t_data *data)
{
	pthread_mutex_lock(&data->error_m);
	if (data->error)
	{
		pthread_mutex_unlock(&data->error_m);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->error_m);
		return (0);
	}
}

void	ft_end_cleaner(t_data *data, t_philo *philo)
{
	if (data->error)
	{
		ft_exit_philo(data, philo);
		return ;
	}
	ft_set_error(data, 9, NULL);
	ft_exit_philo(data, philo);
}

int	ft_exit_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (data->error >= 2)
		pthread_mutex_destroy(&data->error_m);
	if (data->error >= 3 && data->error < 7)
		free(data->forks);
	if (data->error >= 4)
		pthread_mutex_destroy(&data->last_eat_m);
	if (data->error >= 5)
		pthread_mutex_destroy(&data->data_dead_m);
	if (data->error >= 6)
		pthread_mutex_destroy(&data->num_eat_m);
	if (data->error >= 7)
	{
		while (i < data->num_phil)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	if (data->error >= 8 && philo)
		free(philo);
	if (data->error >= 9)
		free(data->philo_t);
	return (0);
}
