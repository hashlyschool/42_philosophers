/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utilit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@students.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:25:03 by hashly            #+#    #+#             */
/*   Updated: 2021/11/29 10:27:21 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_get_min_fork(t_philo *philo)
{
	if (philo->l_fork < philo->r_fork)
		return (philo->l_fork);
	else
		return (philo->r_fork);
}

int	ft_get_max_fork(t_philo *philo)
{
	if (philo->l_fork > philo->r_fork)
		return (philo->l_fork);
	else
		return (philo->r_fork);
}
