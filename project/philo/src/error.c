/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:23:36 by hashly            #+#    #+#             */
/*   Updated: 2021/12/04 14:32:39 by hashly           ###   ########.fr       */
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
int	ft_exit_philo(t_data *data, t_philo *philo)
{
	if (data->error >= 2)
		free(data->forks);
	if (data->error >= 4)
		free(data->philo_t);
	if (data->error >= 3 && philo)
		free(philo);
	return (0);
}

/*
	if error
		вывод сообщения
*/
void	ft_error_str_set_status(t_data *data, int error, char *message)
{
	if (error)
	{
		data->error = error;
		printf("%s", message);
	}
	return ;
}

