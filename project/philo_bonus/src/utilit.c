/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:31:41 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 21:04:42 by hashly           ###   ########.fr       */
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
	sem_wait(philo->data->sem_print);
	if (cond_one_check_time_death(philo))
	{
		printf("%lu %d %s\n", \
		get_time_ms() - philo->data->time_start - START_MS, \
		philo->id, str);
		fflush(stdout);
		sem_post(philo->data->sem_print);
		return (1);
	}
	sem_post(philo->data->sem_print);
	return (0);
}

int	ft_exit(t_data *data, int mode, char *str_err)
{
	data->error = mode;
	printf("%s", str_err);
	if (mode >= 2)
		sem_close(data->sem_forks);
	// if (mode >= 3)
	// 	sem_close(data->sem_death);
	sem_close(data->sem_last_eat);
	sem_close(data->sem_num_eat);
	sem_close(data->sem_print);
	if (mode >= 4)
		free(data->arr_pid);
	return (0);
}
