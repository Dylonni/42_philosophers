/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:00:57 by daumis            #+#    #+#             */
/*   Updated: 2023/07/27 13:51:00 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*This function will create as many forks as needed
and initialize their mutexes*/
void	init_forks(t_data *data, t_philo *nb_philos)
{
	int	i;

	i = 0;
	data->forks = malloc (sizeof(pthread_mutex_t) * data->args[0]);
	if (!data->forks)
		return ;
	while (i < data->args[0])
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	i = 0;
	while (i < data->args[0])
	{
		if (i == data->args[0] - 1)
		{
			nb_philos[i].fork_l = &(data->forks[i]);
			nb_philos[i].fork_r = &(data->forks[0]);
			break ;
		}
		nb_philos[i].fork_l = &(data->forks[i]);
		nb_philos[i].fork_r = &(data->forks[i + 1]);
		i++;
	}
}

/*Initialize mutexes to acces data with threads avoiding data races*/
void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&(data->eating), NULL);
	pthread_mutex_init(&(data->print), NULL);
	pthread_mutex_init(&(data->dead), NULL);
	pthread_mutex_init(&(data->der_rep), NULL);
}

/*Initialize each philosopher's data before creating their threads */
void	init_philos(t_data *data, t_philo *nb_philos, int argc)
{
	int	i;

	i = -1;
	while (++i < data->args[0])
	{
		nb_philos[i].index_philo = i + 1;
		nb_philos[i].sh_data = data;
		pthread_mutex_init(&(nb_philos[i].is_eating), NULL);
		pthread_mutex_init(&(nb_philos[i].ate), NULL);
		nb_philos[i].meal_count = 0;
		nb_philos[i].ac_cpy = argc;
	}
}

/*Loop that will create as many philosophers threads based on args[0].
Also launches the monitor thread*/
int	launch_threads(t_data *data, t_philo *nb_philos)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->args[0])
	{
		if (nb_philos[i].index_philo % 2 == 0)
		{
			if (pthread_create(&nb_philos[i].id_philo, NULL, \
			&routine2, &nb_philos[i]))
				return (1);
		}
		else
			if (pthread_create(&nb_philos[i].id_philo, NULL, \
			&routine, &nb_philos[i]))
				return (1);
		meal_mutex(&(nb_philos[i]));
		data->nb_threads++;
	}
	if (pthread_create(&(data->id_monitor), NULL, &monitor, nb_philos))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*nb_philos;

	ft_memset(&data, 0, sizeof(t_data));
	if (check_args(argc, argv, &data))
		return (freedata(&data), 1);
	nb_philos = malloc (sizeof(t_philo) * data.args[0]);
	if (!nb_philos)
		return (freedata(&data), 1);
	init_forks(&data, nb_philos);
	init_mutexes(&data);
	init_philos(&data, nb_philos, argc);
	if (launch_threads(&data, nb_philos))
	{
		detach_threads(&data, nb_philos);
		destroy_mutexes(nb_philos);
		freedata(&data);
		free(nb_philos);
		return (1);
	}
	join_all(&data, nb_philos);
	destroy_mutexes(nb_philos);
	freedata(&data);
	free(nb_philos);
	return (0);
}
