/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:31:41 by hashly            #+#    #+#             */
/*   Updated: 2021/12/16 09:23:51 by hashly           ###   ########.fr       */
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
		sem_wait(philo->data->sem_death);
		if (get_time_ms() - philo->last_eat <= philo->data->t_die)
			printf("%lu %d %s", time - philo->data->time_start - START_MS, \
			philo->id, str);
		sem_post(philo->data->sem_death);
		return (1);
	}
	return (0);
}

/*
	if error = 1
		без очистки
	else if error = 2
		sem_close(data->sem_forks);
	else if error = 3
		free(data->arr_pid);
	else if error = 4
		free(data->forks);
		free(philo);
		free(data->philo_t);
*/
int	ft_exit(t_data *data, int mode, char *str_err)
{
	data->error = mode;
	printf("%s", str_err);
	if (mode >= 2)
		sem_close(data->sem_forks);
	if (mode >= 3)
		sem_close(data->sem_death);
	if (mode >= 4)
		free(data->arr_pid);
	return (0);
}
