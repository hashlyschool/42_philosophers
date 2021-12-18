/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:24:55 by hashly            #+#    #+#             */
/*   Updated: 2021/12/18 19:26:17 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	cond_check_time(t_philo	*phl)
{
	pthread_mutex_lock(&phl->data->last_eat_m);
	if (get_time_ms() - phl->last_eat <= phl->data->t_die)
	{
		pthread_mutex_unlock(&phl->data->last_eat_m);
		return (1);
	}
	pthread_mutex_unlock(&phl->data->last_eat_m);
	return (0);
}

int	cond_check_eat(t_philo	*phl)
{
	pthread_mutex_lock(&phl->data->num_eat_m);
	if (phl->data->max_eat != -1 && phl->num_eat == phl->data->max_eat)
	{
		pthread_mutex_unlock(&phl->data->num_eat_m);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&phl->data->num_eat_m);
		return (0);
	}
}

/*
 if(mode == 1)
	phl->data->death != 1 && phl->num_eat <= phl->data->max_eat
 if(mode == 2)
	phl->data->death != 1 && phl->num_eat == phl->data->max_eat
 if(mode == 3)
	phl->data->death != 1 && phl->num_eat >= phl->data->max_eat
*/
int	cond_check_data_dead(t_philo *phl, int mode)
{
	pthread_mutex_lock(&phl->data->data_dead_m);
	pthread_mutex_lock(&phl->data->num_eat_m);
	if ((mode == 1 && \
	(phl->data->death != 1 && phl->num_eat <= phl->data->max_eat)) || \
	(mode == 2 && \
	(phl->data->max_eat != -1 && phl->num_eat >= phl->data->max_eat)) || \
	(mode == 3 && \
	(phl->data->max_eat != -1 && phl->num_eat == phl->data->max_eat)))
	{
		pthread_mutex_unlock(&phl->data->num_eat_m);
		pthread_mutex_unlock(&phl->data->data_dead_m);
		return (1);
	}
	pthread_mutex_unlock(&phl->data->num_eat_m);
	pthread_mutex_unlock(&phl->data->data_dead_m);
	return (0);
}
