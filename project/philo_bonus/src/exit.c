/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:55:51 by hashly            #+#    #+#             */
/*   Updated: 2021/12/11 18:34:14 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	if error = 1
		без очистки
	else if error = 2
		sem_close(data->sem_forks);
	else if error = 3
		free(data->arr_pid);
	else if error = 4
		free(data->forks);
		free(philo);
		free(data->philo_t);
*/
int	ft_exit(t_data *data, int mode, char *str_err)
{
	data->error = mode;
	printf("%s", str_err);
	if (mode >= 2)
		sem_close(data->sem_forks);
	if (mode >= 3)
		sem_close(data->sem_check_death);
	if (mode >= 4)
		free(data->arr_pid);
	return (0);
}


int	ft_exit_child(t_data *data, int mode_child, char *str_err)
{
	ft_exit(data, 4, str_err);

	return (0);
}
