/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:40:14 by hashly            #+#    #+#             */
/*   Updated: 2021/12/19 14:25:03 by hashly           ###   ########.fr       */
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
# define TAKE_FORK "has taken a fork\n"
# define EATING "is eating\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"
# define DIED "died\n"
# define START_MS 60
# define SLEEP 500

typedef struct s_data
{
	int				num_phil;
	unsigned long	t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	pthread_mutex_t	*forks;
	pthread_t		*philo_t;
	pthread_mutex_t	last_eat_m;
	pthread_mutex_t	data_dead_m;
	pthread_mutex_t	num_eat_m;
	int				death;
	int				error;
	pthread_mutex_t	error_m;
	unsigned long	time_start;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	unsigned long	last_eat;
	int				num_eat;
	int				l_fork;
	int				r_fork;
	int				max_fork;
	int				min_fork;
}	t_philo;

//philo.c
void			ft_philo(int argc, char **argv);
void			*philo_live(void *arg);
//get_param.c
int				ft_init_data(t_data *data, int argc, char **argv);
//error_exit.c
int				ft_set_error(t_data *data, int error, char *message);
int				ft_check_error(t_data *data);
void			ft_end_cleaner(t_data *data, t_philo *philo);
int				ft_exit_philo(t_data *data, t_philo *philo);
//init.c
int				ft_init_philo(t_data *data, t_philo **arg);
int				ft_init_forks_time(t_data *data);
void			ft_join_thread(t_data *data);
//time.c
void			ft_usleep(int sleep_time_ms);
int				ft_wait_start(t_philo *phl);
unsigned long	get_time_ms(void);
//action.c
int				ft_take_forks(t_philo *philo);
int				ft_eat(t_philo *philo);
int				ft_philo_sleep(t_philo *philo);
int				ft_think(t_philo *philo);
//utilit.c
int				ft_get_min_fork(t_philo *philo);
int				ft_get_max_fork(t_philo *philo);
int				ft_get_r_fork(int i, t_data *data);
int				ft_write_status(t_philo *philo, char *str);
//condition.c
int				cond_check_time(t_philo	*phl);
int				cond_check_eat(t_philo	*phl);
int				cond_check_data_dead(t_philo *phl, int mode);

#endif
