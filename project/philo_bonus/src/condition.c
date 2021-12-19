/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:42:28 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 15:52:54 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	cond_one_check_time_death(t_philo *phl)
{
	sem_wait(phl->data->sem_last_eat);
	if (get_time_ms() - phl->last_eat <= phl->data->t_die)
	{
		sem_post(phl->data->sem_last_eat);
		return (1);
	}
	sem_post(phl->data->sem_last_eat);
	return (0);
}

int	cond_second_check_time_death(t_philo *phl)
{
	sem_wait(phl->data->sem_num_eat);
	if (phl->data->max_eat != -1 && phl->num_eat == phl->data->max_eat)
	{
		sem_post(phl->data->sem_num_eat);
		return (1);
	}
	sem_post(phl->data->sem_num_eat);
	return (0);
}

int	cond_third_check_time_death(t_philo *phl)
{
	sem_wait(phl->data->sem_last_eat);
	if (get_time_ms() - phl->last_eat - phl->data->t_die < 10)
	{
		sem_post(phl->data->sem_last_eat);
		return (1);
	}
	sem_post(phl->data->sem_last_eat);
	return (0);
}
