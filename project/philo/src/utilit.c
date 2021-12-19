/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:25:03 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 14:25:54 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_get_min_fork(t_philo *philo)
{
	if (philo->l_fork < philo->r_fork)
		return (philo->l_fork - 1);
	else
		return (philo->r_fork - 1);
}

int	ft_get_max_fork(t_philo *philo)
{
	if (philo->l_fork > philo->r_fork)
		return (philo->l_fork - 1);
	else
		return (philo->r_fork - 1);
}

int	ft_get_r_fork(int i, t_data *data)
{
	if (i == 1)
		return (data->num_phil);
	else
		return (i - 1);
}

int	ft_write_status(t_philo *philo, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->data_dead_m);
	pthread_mutex_lock(&philo->data->error_m);
	time = get_time_ms();
	if (time && !philo->data->error && \
	time - philo->last_eat <= philo->data->t_die)
	{
		if (philo->data->death == 1)
		{
			pthread_mutex_unlock(&philo->data->error_m);
			pthread_mutex_unlock(&philo->data->data_dead_m);
			return (0);
		}
		printf("%lu %d %s", time - philo->data->time_start - START_MS, \
		philo->id, str);
		pthread_mutex_unlock(&philo->data->error_m);
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->error_m);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (time == 0)
		return (ft_set_error(philo->data, 10, "Error gettimeofday\n"));
	return (0);
}
