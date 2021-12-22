/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:40:14 by hashly            #+#    #+#             */
/*   Updated: 2021/12/22 15:04:04 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//for memset
# include <string.h>
//for printf
# include <stdio.h>
//for malloc, free, exit
# include <stdlib.h>
//for write, usleep, fork
# include <unistd.h>
//for kill
# include <signal.h>
//for gettimeofday
# include <sys/time.h>
//for pthread_create, pthread_detach, pthread_join
# include <pthread.h>
//for waitpid
# include <sys/wait.h>
//for  sem_open, sem_close, sem_post, sem_wait, sem_unlink
# include <sys/stat.h>
# include <semaphore.h>
//for named const
# include <fcntl.h>
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define SLEEP 500
# define START_MS 120

typedef struct s_data
{
	int				num_phil;
	unsigned long	t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	int				death;
	int				error;
	unsigned long	time_start;
	sem_t			*sem_forks;
	sem_t			*sem_last_eat;
	sem_t			*sem_num_eat;
	sem_t			*sem_print;
	pid_t			*arr_pid;
	pthread_t		*philo_thread;

}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	unsigned long	last_eat;
	int				num_eat;
}	t_philo;

//philo.c
void			ft_philo_live(t_data *data, int id);
//get_param.c
void			ft_init_data(t_data *data, int argc, char **argv);
//init.c
void			ft_init_forks_time(t_data *data);
void			ft_init_philo(t_data *data);
t_philo			ft_init_philo_struct(t_data *data, int id);
//utilit.c
void			*ft_waitpid(void *arg);
int				ft_write(t_philo *philo, char *str);
int				ft_write_status(t_philo *philo, char *str);
int				ft_exit(t_data *data, int mode, char *str_err);
//time.c
void			ft_usleep(t_data *data, int sleep_time_ms);
void			ft_wait_start(t_philo *phl);
void			ft_wait_to_time(t_philo *data, int sleep_to_time_ms);
unsigned long	get_time_ms(void);
//action.c
int				ft_take_forks(t_philo *philo);
int				ft_eat(t_philo *philo);
int				ft_philo_sleep(t_philo *philo);
int				ft_think(t_philo *philo);
//condition.c
int				cond_one_check_time_death(t_philo *phl);
int				cond_second_check_time_death(t_philo *phl);
int				cond_third_check_time_death(t_philo *phl);
int				cond_philo_live(t_philo *phl, int mode);
//itoa.c
size_t			ft_strlen(const char *str);
char			*ft_itoa(int n);

#endif
