/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:31:41 by hashly            #+#    #+#             */
/*   Updated: 2021/12/22 15:03:51 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_waitpid(void *arg)
{
	pid_t	*pid;

	pid = (pid_t *)(arg);
	waitpid(*pid, NULL, 0);
	return (NULL);
}

int	ft_exit(t_data *data, int mode, char *str_err)
{
	data->error = mode;
	write(1, str_err, ft_strlen(str_err));
	if (mode >= 4)
		free(data->arr_pid);
	if (mode >= 5)
	{
		sem_close(data->sem_last_eat);
		sem_close(data->sem_num_eat);
		sem_close(data->sem_print);
		sem_close(data->sem_forks);
	}
	return (0);
}

static char	*ft_get_write_str(char *time, char *id, char *str)
{
	size_t	len_str;
	char	*write_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_str = ft_strlen(time) + ft_strlen(id) + ft_strlen(str) + 3;
	write_str = (char *)malloc(sizeof(char ) * (len_str + 1));
	while (time[j])
		write_str[i++] = time[j++];
	j = 0;
	write_str[i++] = ' ';
	while (id[j])
		write_str[i++] = id[j++];
	j = 0;
	write_str[i++] = ' ';
	while (str[j])
		write_str[i++] = str[j++];
	write_str[i++] = '\n';
	write_str[i] = 0;
	return (write_str);
}

int	ft_write(t_philo *philo, char *str)
{
	int		time;
	char	*write_str;
	char	*time_str;
	char	*id_str;

	time = (int)(get_time_ms() - philo->data->time_start - START_MS);
	time_str = ft_itoa(time);
	id_str = ft_itoa(philo->id);
	write_str = ft_get_write_str(time_str, id_str, str);
	write(1, write_str, ft_strlen(write_str));
	free(time_str);
	free(id_str);
	free(write_str);
	return (0);
}

int	ft_write_status(t_philo *philo, char *str)
{
	sem_wait(philo->data->sem_print);
	if (cond_one_check_time_death(philo))
	{
		ft_write(philo, str);
		sem_post(philo->data->sem_print);
		return (1);
	}
	sem_post(philo->data->sem_print);
	return (0);
}
