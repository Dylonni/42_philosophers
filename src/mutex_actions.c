/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:53:06 by daumis            #+#    #+#             */
/*   Updated: 2023/07/27 13:45:33 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*Function that will get the last time the philosopher ate.
Used in routines*/
void	meal_mutex(t_philo *philo)
{
	pthread_mutex_lock(&(philo->is_eating));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->is_eating));
}

/*Function that will update the live status for the watched philo.
Used by monitor*/
void	dead_mutex(t_philo *philo)
{
	pthread_mutex_lock(&(philo->sh_data->dead));
	philo->sh_data->one_die = 1;
	pthread_mutex_unlock(&(philo->sh_data->dead));
}

/*Function that will update the last meal time for the watched philo.
Used by monitor*/
void	get_local_last_meal(long *local_last_meal, t_philo *philo)
{
	pthread_mutex_lock(&(philo->is_eating));
	*local_last_meal = philo->last_meal;
	pthread_mutex_unlock(&(philo->is_eating));
}

/*Function that will increase the local meal count value for the watched philo.
Used by monitor*/
void	get_local_meal_count(int *local_meal_count, t_philo *philo)
{
	pthread_mutex_lock(&(philo->ate));
	*local_meal_count = philo->meal_count;
	pthread_mutex_unlock(&(philo->ate));
}
