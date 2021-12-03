/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@students.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:32:45 by hashly            #+#    #+#             */
/*   Updated: 2021/12/03 11:00:45 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_end_cleaner(t_data *data, t_philo *philo)
{
	if (data->error)
		return ;
	free(data->forks);
	free(data->philo_t);
	free(philo);
}

void	ft_destroy_forks(t_data *data)
{
	int	i;

	if (data->error)
		return ;
	i = 0;
	while (i < data->num_phil)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->time_dead_m);
}

void	ft_join_thread(t_data *data)
{
	int	i;

	if (data->error)
		return ;
	i = 0;
	while (i < data->num_phil)
	{
		pthread_join(data->philo_t[i], NULL);
		i++;
	}
}

void	ft_init_forks_time(t_data *data)
{
	int				i;
	struct timeval	time;

	if (data->error)
		return ;
	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* data->num_phil);
	if (!data->forks)
		return (ft_error_str_set_status(data, "Error malloc for data.forks\n"));
	while (i < data->num_phil)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_error_str_set_status(data, "Error mutex forks init\n"));
		i++;
	}
	if (gettimeofday(&time, NULL))
		ft_error_str_set_status(data, "Error gettimeofday time\n");
	data->time_start = (time.tv_sec * 1000 + time.tv_usec / 1000);
	if (pthread_mutex_init(&data->time_dead_m, NULL))
		return (ft_error_str_set_status(data, "Error mutex init time_dead\n"));
}

t_philo	*init_philo_struct(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->num_phil);
	if (!philo)
		return (NULL);
	i = 1;
	while (i <= data->num_phil)
	{
		philo[i - 1].id = i;
		philo[i - 1].data =  data;
		philo[i - 1].death = 0;
		philo[i - 1].last_eat = 0;
		if (data->max_eat != -1)
			philo[i - 1].num_eat = 0;
		else
			philo[i - 1].num_eat = -1;
		philo[i - 1].l_fork = i;
		philo[i - 1].r_fork = ft_get_r_fork(i, data);
		philo[i - 1].max_fork = ft_get_max_fork(&philo[i - 1]);
		philo[i - 1].min_fork = ft_get_min_fork(&philo[i - 1]);
		i++;
	}
	return (philo);
}

void	ft_init_philo(t_data *data, t_philo *arg)
{
	int		i;

	if (data->error)
		return ;
	data->philo_t = (pthread_t *)malloc(sizeof(pthread_t) * data->num_phil);
	if (!data->philo_t)
		return (ft_error_str_set_status(data, "Error malloc for data.philo\n"));
	i = 0;
	while (i < data->num_phil / 2)
	{
		if (!pthread_create(&data->philo_t[i * 2], NULL, philo_live, &arg[i * 2]))
			i++;
		else
			return (ft_error_str_set_status(data, "Error pthread_create\n"));
	}
	ft_usleep(data, data->t_eat);
	i = 0;
	while (i < data->num_phil / 2)
	{
		if (!pthread_create(&data->philo_t[i * 2 + 1], NULL, philo_live, &arg[i * 2 + 1]))
			i++;
		else
			return (ft_error_str_set_status(data, "Error pthread_create\n"));
	}
	if (data->num_phil % 2)
	{
		i = data->num_phil - 1;
		ft_usleep(data, data->t_eat);
		if (pthread_create(&data->philo_t[i], NULL, philo_live, &arg[i]))
			return (ft_error_str_set_status(data, "Error pthread_create\n"));
	}
}
