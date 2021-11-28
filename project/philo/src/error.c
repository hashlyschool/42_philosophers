/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:23:36 by hashly            #+#    #+#             */
/*   Updated: 2021/11/28 15:04:03 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// void	ft_error_str(char *message)
// {
// 	printf("%s", message);
// 	return ;
// }

void	ft_error_str_set_status(t_data *data, char *message)
{
	data->error = 1;
	printf("%s", message);
	return ;
}
