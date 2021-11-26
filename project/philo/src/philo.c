/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@students.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:30:22 by hashly            #+#    #+#             */
/*   Updated: 2021/11/26 14:49:21 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/philo.h"
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

	init_data(&data, argc, argv);
	// if (!data.error)
	// {
	// 	printf("num phil = %d\nt_die = %d\nt_eat = %d\nt_sleep = %d\nnum_max_eat = %d\n",
	// 	data.num_phil,
	// 	data.t_die,
	// 	data.t_eat,
	// 	data.t_sleep,
	// 	data.max_eat);
	// }
	// init_forks(data);
	// init_time_start(data);
	// init_philo(data);
	// join_thread(data);
	// destroy_forks(data);
	// end_cleaner(data);
}
