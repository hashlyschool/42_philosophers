/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@students.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:20:44 by hashly            #+#    #+#             */
/*   Updated: 2021/11/29 10:29:13 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_take_forks(t_philo *philo)
{
	if (philo->data->death == 1)
		return (0);
	pthread_mutex_lock(&philo->data->forks[ft_get_max_fork(philo)]);
	
}
