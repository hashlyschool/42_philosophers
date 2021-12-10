/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:23:36 by hashly            #+#    #+#             */
/*   Updated: 2021/12/10 16:31:53 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_end_cleaner(t_data *data, t_philo *philo)
{
	if (data->error)
	{
		ft_exit_philo(data, philo);
		return ;
	}
	free(data->forks);
	free(data->philo_t);
	free(philo);
}

void	ft_destroy_forks(t_data *data)
{
	int	i;

	if (data->error)
		return ;
	i = 0;
	while (i < data->num_phil)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->time_dead_m);
}

/*
	if error = 1
		без очистки
	else if error = 2
		free(data->forks);
	else if error = 3
		free(data->forks);
		free(philo);
	else if error = 4
		free(data->forks);
		free(philo);
		free(data->philo_t);
*/
int	ft_exit_philo(t_data *data, t_philo *philo)
{
	if (data->error >= 2)
		free(data->forks);
	if (data->error >= 4)
		free(data->philo_t);
	if (data->error >= 3 && philo)
		free(philo);
	return (0);
}

/*
	if error
		вывод сообщения
*/
void	ft_set_error(t_data *data, int error, char *message)
{
	if (error)
	{
		data->error = error;
		printf("%s", message);
	}
	return ;
}

/*
	if error
		вывод сообщения
*/
void	*ft_set_error2(t_data *data, int error, char *message)
{
	if (error)
	{
		data->error = error;
		printf("%s", message);
	}
	return (NULL);
}
