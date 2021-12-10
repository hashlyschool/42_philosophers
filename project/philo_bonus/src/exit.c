/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:55:51 by hashly            #+#    #+#             */
/*   Updated: 2021/12/10 16:01:32 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	if error = 1
		без очистки
	else if error = 2
		free(data->forks);
	else if error = 3
		free(data->forks);
		free(philo);
	else if error = 4
		free(data->forks);
		free(philo);
		free(data->philo_t);
*/
int	ft_error(t_data *data, int mode, char *str_err)
{
	printf("%s", str_err);
	// if (data->error >= 2)
	// 	free(data->forks);
	// if (data->error >= 4)
	// 	free(data->philo_t);
	// if (data->error >= 3 && philo)
	// 	free(philo);
	return (0);
}
