/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:30:22 by hashly            #+#    #+#             */
/*   Updated: 2021/12/11 22:05:29 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/philo.h"

static void	*check_time_death(void *arg)
{
	t_philo			*phl;

	phl = (t_philo *)arg;
	while (get_time_ms() - phl->last_eat <= phl->data->t_die)
	{
		if (phl->data->max_eat != -1 && phl->num_eat == phl->data->max_eat)
			return (NULL);
		ft_usleep(phl->data, 1);
	}
	if (phl->data->sem_death->__align == 1)
	{
		sem_wait(phl->data->sem_death);
		printf("%lu %d %s", get_time_ms() - phl->data->time_start - START_MS, \
		phl->id, DEID);
	}
	return (NULL);
}

void	ft_philo_live(t_data *data, int id)
{
	t_philo		phl;
	pthread_t	death_t;

	phl = ft_init_philo_struct(data, id);
	ft_wait_start(&phl);
	if (pthread_create(&death_t, NULL, check_time_death, &phl))
		exit(ft_exit(data, 4, "Error. create pthread in ft_philo_live"));
	while (phl.data->death != 1 && phl.num_eat <= phl.data->max_eat)
	{
		if (phl.data->max_eat != -1 && phl.num_eat >= phl.data->max_eat)
			break ;
		if (ft_take_forks(&phl) == 0)
			break ;
		if (ft_eat(&phl) == 0)
			break ;
		if (ft_philo_sleep(&phl) == 0)
			break ;
		if (phl.data->max_eat != -1 && phl.num_eat == phl.data->max_eat)
			break ;
		if (ft_think(&phl) == 0)
			break ;
		ft_usleep(phl.data, 1);
	}
	pthread_join(death_t, NULL);
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

	ft_init_data(&data, argc, argv);
	ft_init_forks_time(&data);
	ft_init_philo(&data);
	ft_exit(&data, 4, "");
}
