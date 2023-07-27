/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:58:25 by daumis            #+#    #+#             */
/*   Updated: 2023/07/25 17:53:04 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*Function used by each philospher to acces the switched value by the monitor.
returns 0 if the value hasn't switched to 1 , else returns 1*/
int	is_philo_alive(t_philo *philo)
{
	int		one_die;
	t_data	*local_data;

	one_die = 0;
	local_data = philo->sh_data;
	pthread_mutex_lock(&(local_data->dead));
	one_die = local_data->one_die;
	pthread_mutex_unlock(&(local_data->dead));
	return (one_die);
}

/*This function will print what a philosopher is doing, based on
if all of them are alive or not*/
void	print_action(char *str, t_philo *philo, int is_dead)
{
	t_data	*local_data;

	local_data = philo->sh_data;
	if (!is_dead)
	{
		pthread_mutex_lock(&(local_data->print));
		printf("%ld %d %s\n", (get_time() - local_data->start_time), \
		philo->index_philo, str);
		pthread_mutex_unlock(&(local_data->print));
	}
}

/*Thread created by launch_philo() to make each
philosopher doing it's routine as long as he is alive.*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_philo_alive(philo))
	{
		pthread_mutex_lock(philo->fork_l);
		print_action("has taken a fork", philo, is_philo_alive(philo));
		if (philo->sh_data->args[0] == 1)
			return ((void)(pthread_mutex_unlock(philo->fork_l)), NULL);
		pthread_mutex_lock(philo->fork_r);
		print_action("has taken a fork", philo, is_philo_alive(philo));
		print_action("is eating", philo, is_philo_alive(philo));
		ft_usleep(philo->sh_data->args[2]);
		meal_mutex(philo);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_lock(&(philo->ate));
		philo->meal_count += 1;
		pthread_mutex_unlock(&(philo->ate));
		print_action("is sleeping", philo, is_philo_alive(philo));
		ft_usleep(philo->sh_data->args[3]);
		print_action("is thinking", philo, is_philo_alive(philo));
	}
	return (NULL);
}

/*Thread created by launch_philo() to make each
philosopher doing it's routine as long as he is alive.
 
The difference with routine() is that this function is launched
every even philo making a sleep() before executing the routine,
thus preventing forks stealing.*/
void	*routine2(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->sh_data->args[2]);
	while (!is_philo_alive(philo))
	{
		pthread_mutex_lock(philo->fork_r);
		print_action("has taken a fork", philo, is_philo_alive(philo));
		pthread_mutex_lock(philo->fork_l);
		print_action("has taken a fork", philo, is_philo_alive(philo));
		print_action("is eating", philo, is_philo_alive(philo));
		ft_usleep(philo->sh_data->args[2]);
		meal_mutex(philo);
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_lock(&(philo->ate));
		philo->meal_count += 1;
		pthread_mutex_unlock(&(philo->ate));
		print_action("is sleeping", philo, is_philo_alive(philo));
		ft_usleep(philo->sh_data->args[3]);
		print_action("is thinking", philo, is_philo_alive(philo));
	}
	return (NULL);
}
