/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:44 by hashly            #+#    #+#             */
/*   Updated: 2021/12/14 10:08:32 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_take_forks(t_philo *philo)
{
	if (philo->data->death == 1)
		return (0);
	pthread_mutex_lock(&philo->data->forks[philo->min_fork]);
	if (ft_write_status(philo, TAKE_FORK) == 0 || philo->data->num_phil == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->forks[philo->max_fork]);
	if (ft_write_status(philo, TAKE_FORK) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		return (0);
	}
	return (1);
}

int	ft_eat(t_philo *philo)
{
	if (philo->data->death == 1)
		return (0);
	if (ft_write_status(philo, EATING) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	ft_usleep(philo->data, philo->data->t_eat);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
	if (philo->num_eat != -1)
		philo->num_eat++;
	return (1);
}

int	ft_philo_sleep(t_philo *philo)
{
	if (philo->data->death == 1)
		return (0);
	if (ft_write_status(philo, SLEEPING) == 0)
		return (0);
	ft_usleep(philo->data, philo->data->t_sleep);
	return (1);
}

int	ft_think(t_philo *philo)
{
	if (philo->data->death == 1)
		return (0);
	if (ft_write_status(philo, THINKING) == 0)
		return (0);
	if (philo->data->t_eat > philo->data->t_sleep)
		ft_usleep(philo->data, philo->data->t_eat - philo->data->t_sleep);
	ft_usleep(philo->data, 2);
	return (1);
}
