/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:30:22 by hashly            #+#    #+#             */
/*   Updated: 2021/12/21 16:03:29 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/philo.h"

static void	*check_time_death(void *arg)
{
	t_philo			*phl;

	phl = (t_philo *)arg;
	while (cond_one_check_time_death(phl))
	{
		if (cond_second_check_time_death(phl))
			return (NULL);
		ft_usleep(phl->data, 1);
	}

	sem_wait(phl->data->sem_print);
	if (cond_third_check_time_death(phl))
	{
		printf("%lu %d %s\n", get_time_ms() - phl->data->time_start - START_MS, \
		phl->id, DIED);
		ft_usleep(phl->data, phl->data->t_die * 2);
	}
	sem_wait(phl->data->sem_death);
	phl->data->death = 1;
	sem_post(phl->data->sem_death);
	sem_post(phl->data->sem_print);
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
	while (cond_philo_live(&phl, 1))
	{
		if (cond_philo_live(&phl, 2))
			break ;
		if (ft_take_forks(&phl) == 0)
			break ;
		if (ft_eat(&phl) == 0)
			break ;
		if (ft_philo_sleep(&phl) == 0)
			break ;
		if (cond_philo_live(&phl, 3))
			break ;
		if (ft_think(&phl) == 0)
			break ;
		ft_usleep(phl.data, 1);
	}
	pthread_join(death_t, NULL);
	ft_exit(data, 4, "");
	exit(0);
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
	return (0);
}
