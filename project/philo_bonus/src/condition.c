/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:42:28 by hashly            #+#    #+#             */
/*   Updated: 2021/12/21 17:04:03 by hashly           ###   ########.fr       */
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

int	cond_philo_live(t_philo *phl, int mode)
{
	// sem_wait(phl->data->sem_death);
	sem_wait(phl->data->sem_num_eat);
	if ((mode == 1 && \
	(cond_one_check_time_death(phl) && phl->num_eat <= phl->data->max_eat)) || \
	(mode == 2 && \
	(phl->data->max_eat != -1 && phl->num_eat >= phl->data->max_eat)) || \
	(mode == 3 && \
	(phl->data->max_eat != -1 && phl->num_eat == phl->data->max_eat)))
	{
		sem_post(phl->data->sem_num_eat);
		// sem_post(phl->data->sem_death);
		return (1);
	}
	sem_post(phl->data->sem_num_eat);
	// sem_post(phl->data->sem_death);
	return (0);
}
