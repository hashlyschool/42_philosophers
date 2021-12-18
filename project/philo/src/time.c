/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:44:50 by hashly            #+#    #+#             */
/*   Updated: 2021/12/18 18:20:42 by hashly           ###   ########.fr       */
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
четные философы ждут от времени старта START_MS мс + t_eat,
а не четные философы ждут START_MS мс
если философов нечетное количество,
то последний философ ждет START_MS * 2 мс
*/
void	ft_wait_start(t_philo *phl)
{
	int	first;
	int	second;
	int	third;

	first = START_MS;
	second = START_MS + phl->data->t_eat;
	third = START_MS * 2 + phl->data->t_eat;
	if (phl->data->num_phil == 1)
		ft_wait_to_time(phl, first);
	else if (phl->id % 2 == 0)
		ft_wait_to_time(phl, second);
	else
	{
		if (phl->data->num_phil % 2 == 0)
			ft_wait_to_time(phl, first);
		else
		{
			if (phl->id == phl->data->num_phil)
				ft_wait_to_time(phl, third);
			else
				ft_wait_to_time(phl, first);
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
		usleep(SLEEP);
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
		usleep(SLEEP);
		now = get_time_ms();
		if (now == 0)
			return (ft_set_error(data, 4, "Error gettimeofday in ft_usleep\n"));
	}
}
