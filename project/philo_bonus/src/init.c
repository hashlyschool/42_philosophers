/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:32:45 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 15:37:36 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_init_forks_time(t_data *data)
{
	struct timeval	time;

	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("last_eat");
	sem_unlink("num_eat");
	data->sem_forks = sem_open("forks", O_CREAT, 0660, data->num_phil);
	data->sem_death = sem_open("death", O_CREAT, 0660, 1);
	data->sem_last_eat = sem_open("last_eat", O_CREAT, 0660, 1);
	data->sem_num_eat = sem_open("num_eat", O_CREAT, 0660, 1);
	if (data->sem_forks == SEM_FAILED)
		exit(ft_exit(data, 1, "Error sem_open\n"));
	if (data->sem_death == SEM_FAILED)
		exit(ft_exit(data, 2, "Error sem_check_death\n"));
	if (data->sem_last_eat == SEM_FAILED)
		exit(ft_exit(data, 2, "Error.  sem_\n"));
	if (data->sem_num_eat == SEM_FAILED)
		exit(ft_exit(data, 2, "Error sem_\n"));
	if (gettimeofday(&time, NULL))
		exit(ft_exit(data, 3, "Error gettimeofday time. In init time\n"));
	data->time_start = (time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_philo	ft_init_philo_struct(t_data *data, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.data = data;
	if (data->max_eat != -1)
		philo.num_eat = 0;
	else
		philo.num_eat = -1;
	philo.last_eat = data->time_start + START_MS;
	return (philo);
}

static void	ft_init_wait_pthread(t_data *data)
{
	int	i;

	data->philo_thread = (pthread_t *)malloc(sizeof(pthread_t) \
	* data->num_phil);
	if (data->philo_thread == NULL)
		exit(ft_exit(data, 4, "Error malloc, init philo_thread"));
	i = 0;
	while (i < data->num_phil)
	{
		if (!pthread_create(&data->philo_thread[i], NULL, \
		ft_waitpid, &(data->arr_pid[i])))
			i++;
		else
		{
			free(data->philo_thread);
			exit(ft_exit(data, 4, "Error pthread_create\n"));
		}
	}
	i = 0;
	while (i < data->num_phil)
	{
		pthread_join(data->philo_thread[i], NULL);
		i++;
	}
	free(data->philo_thread);
}

/*
Функция создает процессы по количеству философов и запускает симуляцию
Также функция создает потоки по количеству философов в главном процессе.
Эти потоки ждут завершения всех дочерних процессов, а затем
присоединяются к главному процессу
*/
void	ft_init_philo(t_data *data)
{
	int		i;
	pid_t	fd;

	data->arr_pid = (int *)malloc(sizeof(int) * data->num_phil);
	if (data->arr_pid == NULL)
		exit(ft_exit(data, 3, "Error malloc in init philo\n"));
	fd = 1;
	i = -1;
	while (++i < data->num_phil)
	{
		if (fd != 0)
		{
			fd = fork();
			if (fd == -1)
				exit(ft_exit(data, 4, "Error fork in ft_init_philo\n"));
			if (fd != 0)
				data->arr_pid[i] = fd;
		}
		if (fd == 0)
			ft_philo_live(data, i);
	}
	if (fd != 0)
		ft_init_wait_pthread(data);
}
