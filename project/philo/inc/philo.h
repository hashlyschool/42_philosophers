/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@students.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:40:14 by hashly            #+#    #+#             */
/*   Updated: 2021/11/26 14:52:47 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//for memset
# include <string.h>
//for printf
# include<stdio.h>
//for malloc, free
# include<stdlib.h>
//for write, usleep,
# include<unistd.h>
//for gettimeofday
# include <sys/time.h>
//for	pthread_create, pthread_detach, pthread_join,
//		pthread_mutex_lock, pthread_mutex_unlock,
//		pthread_mutex_init, pthread_mutex_destroy
# include <pthread.h>

typedef struct s_data
{
	//input
	int	num_phil;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	max_eat;

	//forks
	pthread_mutex_t	*forks;
	//philo
	pthread_t	*philo;
	//error
	int	error;
}	t_data;

//philo.c
void	ft_philo(int argc, char **argv);
//get_param.c
void	init_data(t_data *data, int argc, char **argv);

#endif
