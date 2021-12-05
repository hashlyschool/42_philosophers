/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:44:50 by hashly            #+#    #+#             */
/*   Updated: 2021/12/05 18:59:23 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
Философы не могут все одновременно сесть за стол,
Поэтому:
четные философы ждут от времени старта num_phil * MS_SLEEP_START мс  + t_eat,
а не четные философы ждут num_phil * MS_SLEEP_START мс
если философов нечетное количество,
то последний философ ждет num_phil * MS_SLEEP_START мс + 2 * t_eat
*/
void	ft_wait_start(t_philo *phl)
{
	if (phl->id % 2 == 0)
		ft_wait_to_time(phl, phl->data->num_phil * START_MS + phl->data->t_eat);
	else
	{
		if (phl->data->num_phil % 2 == 0)
			ft_wait_to_time(phl, phl->data->num_phil * START_MS);
		else
		{
			if (phl->id == phl->data->num_phil)
				ft_wait_to_time(phl, phl->data->num_phil * START_MS + \
				phl->data->t_eat * 2);
			else
				ft_wait_to_time(phl, phl->data->num_phil * START_MS);
		}
	}
	return ;
}

void	ft_wait_to_time(t_philo *phl, int sleep_to_time_ms)
{
	unsigned long	start;
	unsigned long	now;

	start = phl->data->time_start;
	now = get_time_ms();
	while (now < start + sleep_to_time_ms)
	{
		usleep(50);
		now = get_time_ms();
		if (now == 0)
			return (ft_set_error(phl->data, 4, \
			"Error gettimeofday in ft_usleep\n"));
	}
}

void	ft_usleep(t_data *data, int sleep_time_ms)
{
	unsigned long	start;
	unsigned long	now;

	start = get_time_ms();
	if (start == 0)
		return (ft_set_error(data, 4, "Error gettimeofday in ft_usleep\n"));
	now = start;
	while (now < start + sleep_time_ms)
	{
		usleep(50);
		now = get_time_ms();
		if (now == 0)
			return (ft_set_error(data, 4, "Error gettimeofday in ft_usleep\n"));
	}
}
