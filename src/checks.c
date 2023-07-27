/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:24:58 by daumis            #+#    #+#             */
/*   Updated: 2023/07/27 13:48:36 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*Function that displays an error before quiting the prgoram, frees data ptr*/
void	errmsg(t_data *data, int errno)
{
	write(2, "Error\n", 7);
	if (errno == 1)
	{
		write(2, "Invalid Arguments\n", 19);
		write(2, "Usage: <nb of philos> <time to die> <time to eat>", 50);
		write(2, " <time to sleep> <philo must eat> (optionnal)\n", 47);
	}
	if (errno == 2)
		write(2, "Nb of philos must be between 1 and 200\n", 39);
	if (errno == 3)
		write(2, "Arguments can't be set to 0\n", 29);
	freedata(data);
}

/*This function will check if it's given parameters are integers or not*/
int	check_int(char *s)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i] == '-' || s[i] == '+')
	{
		sign++;
		i++;
	}
	if (sign > 0)
		return (0);
	if (!(ft_isdigit(s[i])))
		return (0);
	return (1);
}

/*Checks if the inputs are correct for the program to run
properly. Stores the parameters into an array of int*/
int	check_input(char *s, t_data *data)
{
	long	num;
	int		flag;

	num = 0;
	flag = 0;
	if (check_int(s))
		num = ft_atoi(s, &flag);
	else
		return (1);
	if (flag)
		return (1);
	data->args[data->nb_arg] = num;
	data->nb_arg++;
	return (0);
}

/*This function will determine if everything is correct for
the program to run properly, throws an error msg if not*/
int	check_args(int argc, char *argv[], t_data *data)
{
	int	i;

	i = 1;
	data->args = malloc ((argc - 1) * sizeof(long));
	if (!data->args)
		return (1);
	if ((argc < 5) || (argc > 6))
		return (1);
	while (i < argc)
	{
		if (check_input(argv[i], data))
			return (errmsg(data, 1), 1);
		i++;
	}
	if (data->args[0] < 1 || data->args[0] > 200)
		return (errmsg(data, 2), 1);
	if (data->args[1] == 0 || data->args[2] == 0
		|| data->args[3] == 0 || (argc == 6 && data->args[4] == 0))
		return (errmsg(data, 3), 1);
	return (0);
}
