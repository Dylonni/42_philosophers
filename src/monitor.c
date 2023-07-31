/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:49:12 by daumis            #+#    #+#             */
/*   Updated: 2023/07/27 13:43:46 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*Modified function of usleep to match millisecs*/
void	ft_usleep(long milisec)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milisec)
		usleep(100);
}

/*This function will use the timeoftheday internal function and applies 
conversion to it , allowing user to get the curent time in milliseconds*/
long	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

/*Thread that will watch on each philosopher. Once a philosopher dies or
once each philosophers ate the right amount of meals, the monitor will
switch a value, allowing all the threads and the program to stop*/
void	*monitor(void *arg)
{
	t_philo			*philos;
	t_var_monitor	vars;

	philos = (t_philo *)arg;
	ft_memset(&vars, 0, sizeof(t_var_monitor));
	vars.nb_philos = philos[0].sh_data->args[0];
	while (1)
	{
		vars.i = -1;
		vars.flag = 0;
		while (++vars.i < vars.nb_philos)
		{
			get_local_last_meal(&(vars.last_meal), &(philos[vars.i]));
			get_local_meal_count(&(vars.meal_count), &(philos[vars.i]));
			if (philos[0].sh_data->args[1] < (get_time() - vars.last_meal))
				return (print_action("Has died", &(philos[vars.i]), 0), \
				dead_mutex(&(philos[vars.i])), NULL);
			if (philos[0].ac_cpy == 6 && \
			(vars.meal_count >= philos[vars.i].sh_data->args[4]))
				vars.flag++;
		}
		if (vars.flag == vars.nb_philos)
			return (dead_mutex(&(philos[0])), NULL);
		usleep(100);
	}
}
