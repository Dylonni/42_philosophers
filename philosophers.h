/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:39:38 by daumis            #+#    #+#             */
/*   Updated: 2023/07/27 13:48:36 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

/*Data Collection*/
typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	der_rep;
	pthread_t		id_monitor;
	long			*args;
	long			start_time;
	int				nb_arg;
	int				nb_threads;
	int				one_die;
}	t_data;

/*Philosopher structure*/
typedef struct s_philo
{
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	ate;
	pthread_t		id_philo;
	t_data			*sh_data;
	long			last_meal;
	int				meal_count;
	int				ac_cpy;
	int				index_philo;
}	t_philo;

/*Monitor Variables*/
typedef struct s_var_monitor
{
	long	last_meal;
	int		meal_count;
	int		i;
	int		flag;
	long	nb_philos;
}	t_var_monitor;

/*Tools Functions*/

void	*ft_memset(void *s, int c, size_t n);
void	errmsg(t_data *data, int errno);
void	ft_usleep(long milisec);
void	freedata(t_data *data);
void	detach_threads(t_data *data, t_philo *nb_philos);
long	get_time(void);
int		ft_atoi(char *str, int *flag);
int		check_input(char *s, t_data *data);
int		check_int(char *s);
int		signhandle(char c, int sign);
int		ft_isspace(char c);
int		ft_isdigit(int c);

/*Main functions*/

void	*monitor(void *arg);
void	*routine(void *arg);
void	*routine2(void *arg);
void	init_mutexes(t_data *data);
void	init_forks(t_data *data, t_philo *nb_philos);
void	init_philos(t_data *data, t_philo *nb_philos, int argc);
void	print_action(char *str, t_philo *philo, int is_dead);
void	meal_mutex(t_philo *philo);
void	dead_mutex(t_philo *philo);
void	get_local_last_meal(long *local_last_meal, t_philo *philo);
void	get_local_meal_count(int *local_meal_count, t_philo *philo);
void	destroy_mutexes(t_philo *nb_philos);
void	join_all(t_data *data, t_philo *nb_philos);
int		check_args(int argc, char *argv[], t_data *data);
int		is_philo_alive(t_philo *philo);
int		launch_threads(t_data *data, t_philo *nb_philos);

#endif