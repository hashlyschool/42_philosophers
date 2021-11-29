/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@students.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:30:22 by hashly            #+#    #+#             */
/*   Updated: 2021/11/29 10:14:12 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/philo.h"

void	*check_time_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time_ms() - philo->last_eat <= philo->data->t_die)
	{
		philo->death = 1;
		ft_usleep(philo->data, 1);
	}
	if (pthread_mutex_lock(&philo->data->time_dead_m))
	{
		ft_error_str_set_status(philo->data, "Error mutex lock in check_time_death\n");
		return (NULL);
	}
	if (philo->data->death != 1)
	{
		philo->data->death = 1;
		printf("%lu %d died\n", get_time_ms() - philo->last_eat, philo->id);
	}
	if (pthread_mutex_unlock(&philo->data->time_dead_m))
		ft_error_str_set_status(philo->data, "Error mutex unlock in check_time_death\n");
	return (NULL);
}

/*

*/
void	*philo_live(void *arg)
{
	t_philo			*philo;
	pthread_t		death_t;

	philo = (t_philo *)arg;
	philo->last_eat = philo->data->time_start;
	pthread_create(&death_t, NULL, check_time_death, &(*philo));
	while (philo->data->death != 1)
	{
		if (philo->data->max_eat != -1 && philo->num_eat >= philo->data->max_eat)
			break ;
		if (ft_take_forks(philo) == 0)
			break ;
		if (ft_eat(philo) == 0)
			break ;
		if (philo->data->max_eat != -1 && philo->num_eat == philo->data->max_eat)
			break ;
		if (ft_philo_sleep(philo) == 0)
			break ;
		if (ft_think(philo) == 0)
			break ;
		ft_usleep(philo->data, 1);
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
			return (ft_error_str_set_status(&data, "Error malloc in init philo struct\n"));
	}
	ft_init_philo(&data, arg);
	ft_join_thread(&data);
	ft_destroy_forks(&data);
	ft_end_cleaner(&data);
}
