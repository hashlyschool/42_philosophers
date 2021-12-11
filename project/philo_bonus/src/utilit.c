/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:31:41 by hashly            #+#    #+#             */
/*   Updated: 2021/12/11 19:28:16 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_waitpid(void *arg)
{
	pid_t	*pid;

	pid = (pid_t *)(arg);
	waitpid(*pid, NULL, 0);
	return (NULL);
}

int	ft_write_status(t_philo *philo, char *str)
{
	unsigned long	time;

	time = get_time_ms();
	if (time - philo->last_eat <= philo->data->t_die)
	{
		if (philo->data->death == 1)
			return (0);
		sem_wait(philo->data->sem_check_death);
		printf("%lu %d %s", \
		time - philo->data->time_start - START_MS, \
		philo->id, str);
		sem_post(philo->data->sem_check_death);
		return (1);
	}
	return (0);
}
