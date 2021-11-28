/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:44:50 by hashly            #+#    #+#             */
/*   Updated: 2021/11/28 22:02:09 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(t_data *data, int sleep_time_ms)
{
	unsigned long int	start;
	unsigned long int	now;
	struct timeval		time;

	if (gettimeofday(&time, NULL))
		return (ft_error_str_set_status(data, "Error gettimeofday in ft_usleep\n"));
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	now = start;
	while (now < start + sleep_time_ms)
	{
		usleep(30);
		if (gettimeofday(&time, NULL))
			return (ft_error_str_set_status(data, "Error gettimeofday in ft_usleep\n"));
		now = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
}
