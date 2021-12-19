/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:32:45 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 14:25:10 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_mutex_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->last_eat_m, NULL))
		return (ft_set_error(data, 3, "Error init  mutex\n"));
	if (pthread_mutex_init(&data->data_dead_m, NULL))
		return (ft_set_error(data, 4, "Error init  mutex\n"));
	if (pthread_mutex_init(&data->num_eat_m, NULL))
		return (ft_set_error(data, 5, "Error init  mutex\n"));
	i = 0;
	while (i < data->num_phil)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&data->forks[--i]);
			return (ft_set_error(data, 6, "Error init  mutex\n"));
		}
	}
	return (0);
}

int	ft_init_forks_time(t_data *data)
{
	struct timeval	time;

	if (ft_check_error(data))
		return (0);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* data->num_phil);
	if (!data->forks)
		return (ft_set_error(data, 2, "Error malloc for data.forks\n"));
	if (gettimeofday(&time, NULL))
		return (ft_set_error(data, 3, "Error malloc for data.forks\n"));
	data->time_start = (time.tv_sec * 1000 + time.tv_usec / 1000);
	ft_mutex_init(data);
	return (0);
}

void	ft_join_thread(t_data *data)
{
	int	i;

	if (ft_check_error(data))
		return ;
	i = 0;
	while (i < data->num_phil)
	{
		pthread_join(data->philo_t[i], NULL);
		i++;
	}
}

static t_philo	*init_philo_struct(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->num_phil);
	if (!philo)
		ft_set_error(data, 7, "Error malloc philo\n");
	if (ft_check_error(data))
		return (NULL);
	i = 0;
	while (++i <= data->num_phil)
	{
		philo[i - 1].id = i;
		philo[i - 1].data = data;
		philo[i - 1].last_eat = 0;
		if (data->max_eat != -1)
			philo[i - 1].num_eat = 0;
		else
			philo[i - 1].num_eat = -1;
		philo[i - 1].l_fork = i;
		philo[i - 1].r_fork = ft_get_r_fork(i, data);
		philo[i - 1].max_fork = ft_get_max_fork(&philo[i - 1]);
		philo[i - 1].min_fork = ft_get_min_fork(&philo[i - 1]);
		philo[i - 1].last_eat = data->time_start + START_MS;
	}
	return (philo);
}

int	ft_init_philo(t_data *data, t_philo **arg)
{
	int		i;

	if (ft_check_error(data))
		return (0);
	*arg = init_philo_struct(data);
	if (ft_check_error(data))
		return (0);
	data->philo_t = (pthread_t *)malloc(sizeof(pthread_t) * data->num_phil);
	if (!data->philo_t)
		return (ft_set_error(data, 8, "Error malloc for data.philo\n"));
	i = -1;
	while (++i < data->num_phil)
	{
		if (pthread_create(&data->philo_t[i], NULL, philo_live, &(*arg)[i]))
		{
			ft_set_error(data, 9, "Error pthread create\n");
			while (--i >= 0)
				pthread_join(data->philo_t[i], NULL);
			return (0);
		}
	}
	return (0);
}
