/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:44 by hashly            #+#    #+#             */
/*   Updated: 2021/11/30 13:49:06 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_take_forks(t_philo *philo)
{
	if (philo->data->death == 1)
		return (0);
	pthread_mutex_lock(&philo->data->forks[philo->min_fork]);
	if (ft_write_status(philo, "as taken a fork\n") == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->forks[philo->max_fork]);
	if (ft_write_status(philo, "as taken a fork\n") == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		return (0);
	}
	return (1);
}
