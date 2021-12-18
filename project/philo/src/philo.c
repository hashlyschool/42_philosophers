/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:30:22 by hashly            #+#    #+#             */
/*   Updated: 2021/12/18 19:20:03 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/philo.h"

static t_philo	*init_philo_struct(t_data *data)
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
		i++;
	}
	return (philo);
}

void	*check_time_death(void *arg)
{
	t_philo	*phl;

	phl = (t_philo *)arg;
	while (cond_check_time(phl))
	{
		if (cond_check_eat(phl))
			return (NULL);
		ft_usleep(phl->data, 1);
	}
	pthread_mutex_lock(&phl->data->data_dead_m);
	if (phl->data->death != 1)
	{
		phl->data->death = 1;
		printf("%lu %d %s", get_time_ms() - phl->data->time_start - START_MS, \
		phl->id, DIED);
	}
	pthread_mutex_unlock(&phl->data->data_dead_m);
	return (NULL);
}

/*
	Главная функция для жизни философов
*/
void	*philo_live(void *arg)
{
	t_philo			*phl;
	pthread_t		death_t;

	phl = (t_philo *)arg;
	ft_wait_start(phl);
	pthread_create(&death_t, NULL, check_time_death, phl);
	while (cond_check_data_dead(phl, 1))
	{
		if (cond_check_data_dead(phl, 2))
			break ;
		if (ft_take_forks(phl) == 0)
			break ;
		if (ft_eat(phl) == 0)
			break ;
		if (ft_philo_sleep(phl) == 0)
			break ;
		if (cond_check_data_dead(phl, 3))
			break ;
		if (ft_think(phl) == 0)
			break ;
	}
	pthread_join(death_t, NULL);
	return (NULL);
}

/*
input:
	argc == 5 || argc == 6
	argv = [
		"number_of_philosophers"
		"time_to_die"
		"time_to_eat"
		"time_to_sleep"
		["number_of_times_each_philosopher_must_eat"]
	]
*/
void	ft_philo(int argc, char **argv)
{
	t_data	data;
	t_philo	*arg;

	init_data(&data, argc, argv);
	ft_init_forks_time(&data);
	if (data.error == 0)
	{
		arg = init_philo_struct(&data);
		if (!arg)
			ft_set_error(&data, 2, \
			"Error malloc for philo in init_philo_struct\n");
	}
	if (data.error)
	{
		ft_exit_philo(&data, NULL);
		return ;
	}
	ft_init_philo(&data, arg);
	ft_join_thread(&data);
	ft_destroy_forks(&data);
	ft_end_cleaner(&data, arg);
}

int	main(int argc, char **argv)
{
	ft_philo(argc, argv);
	return (0);
}
