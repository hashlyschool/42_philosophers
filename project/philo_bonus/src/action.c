/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:44 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 15:40:59 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_take_forks(t_philo *philo)
{
	if (philo->data->death == 1)
		return (0);
	sem_wait(philo->data->sem_forks);
	if (ft_write_status(philo, TAKE_FORK) == 0 || philo->data->num_phil == 1)
	{
		sem_post(philo->data->sem_forks);
		return (0);
	}
	sem_wait(philo->data->sem_forks);
	if (ft_write_status(philo, TAKE_FORK) == 0)
	{
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
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
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
		return (0);
	}
	ft_usleep(philo->data, philo->data->t_eat);
	sem_wait(philo->data->sem_last_eat);
	philo->last_eat = get_time_ms();
	sem_post(philo->data->sem_last_eat);
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
	sem_wait(philo->data->sem_num_eat);
	if (philo->num_eat != -1)
		philo->num_eat++;
	sem_post(philo->data->sem_num_eat);
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
	return (1);
}
