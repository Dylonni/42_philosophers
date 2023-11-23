/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:54:24 by daumis            #+#    #+#             */
/*   Updated: 2023/07/27 13:48:25 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*This function will free the data pointer if its freeable*/
void	freedata(t_data *data)
{
	if (data->args)
	{
		free(data->args);
		data->args = NULL;
	}
}

/*This function is called upon a pthread_create failure.
It will detach each previous threads that have been created prior to the
error thread */
void	detach_threads(t_data *data, t_philo *nb_philos)
{
	printf("nb threads %d", data->nb_threads);
	while (data->nb_threads > 0)
	{
		pthread_detach(nb_philos[data->nb_threads - 1].id_philo);
		data->nb_threads--;
	}
}

/*Destroy all mutexes that have been initialized before quiting the program*/
void	destroy_mutexes(t_philo *nb_philos)
{
	int	i;

	i = 0;
	if (nb_philos)
	{
		if (nb_philos->sh_data->forks)
		{
			while (i < nb_philos->sh_data->args[0])
			{
				pthread_mutex_destroy(&(nb_philos->sh_data->forks[i]));
				pthread_mutex_destroy(&(nb_philos[i].is_eating));
				i++;
			}
		}
		pthread_mutex_destroy(&(nb_philos->sh_data->eating));
		pthread_mutex_destroy(&(nb_philos->sh_data->print));
		pthread_mutex_destroy(&(nb_philos->sh_data->dead));
		pthread_mutex_destroy(&(nb_philos->sh_data->der_rep));
		free(nb_philos->sh_data->forks);
	}
}

/*Joins all threads that have been created before
quiting the program*/
void	join_all(t_data *data, t_philo *nb_philos)
{
	int	i;

	i = 0;
	pthread_join(data->id_monitor, NULL);
	while (i < data->args[0])
	{
		pthread_join(nb_philos[i].id_philo, NULL);
		i++;
	}
}
