/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:41:11 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 00:34:05 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_atoi(const char *str)
{
	int		n;
	int		flag;
	size_t	len_num;

	n = 0;
	flag = 1;
	len_num = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			flag *= -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str++ - '0');
		if (len_num++ > 12 && flag == 1)
			return (-1);
		else if (len_num > 12 && flag == -1)
			return (0);
	}
	return (n * flag);
}

static void	ft_set_def_param(t_data *data)
{
	data->error = 0;
	data->max_eat = -1;
	data->death = 0;
	data->time_start = 0;
	return ;
}

static int	ft_get_param(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		ft_set_error(data, 2, "Invalid number of arguments. Need 5 or 6\n");
	else
	{
		data->num_phil = ft_atoi(argv[1]);
		data->t_die = ft_atoi(argv[2]);
		data->t_eat = ft_atoi(argv[3]);
		data->t_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->max_eat = ft_atoi(argv[5]);
	}
	if (data->error)
		return (0);
	if (data->num_phil < 0 || data->t_die < 1 || data->t_sleep < 1 || \
	data->t_eat < 1 || data->t_sleep < 1 || (argc == 6 && data->max_eat < 0))
		return (ft_set_error(data, 2, "Incorrect parameters entered\n"));
	return (0);
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	if (pthread_mutex_init(&data->error_m, NULL))
		return (ft_set_error(data, 1, "Error init  mutex\n"));
	ft_set_def_param(data);
	ft_get_param(data, argc, argv);
	return (0);
}
