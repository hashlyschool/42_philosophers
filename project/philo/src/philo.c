/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:30:22 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 14:24:32 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/philo.h"

void	*check_time_death(void *arg)
{
	t_philo	*phl;

	phl = (t_philo *)arg;
	while (cond_check_time(phl))
	{
		if (cond_check_eat(phl))
			return (NULL);
		ft_usleep(1);
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
	Main function for live philo
*/
void	*philo_live(void *arg)
{
	t_philo			*phl;
	pthread_t		death_t;

	phl = (t_philo *)arg;
	if (ft_check_error(phl->data))
		return (NULL);
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
int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	ft_init_data(&data, argc, argv);
	ft_init_forks_time(&data);
	ft_init_philo(&data, &philo);
	ft_join_thread(&data);
	ft_end_cleaner(&data, philo);
	return (0);
}
