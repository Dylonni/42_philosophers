/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dylan <dylan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:05:54 by dylan             #+#    #+#             */
/*   Updated: 2023/07/20 22:06:44 by dylan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*Checks if the given char is a digit ('0' to '9')*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*Checks if the given char is a space. Returns 1 if it is , else returns 0*/
int	ft_isspace(char c)
{
	if ((c == ' ') || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/*Checks if the given char is a negative sign, returns -1 if it is*/
int	signhandle(char c, int sign)
{
	if (c == '-')
		sign *= -1;
	return (sign);
}

/*Ascii TO Int : Transforms a string (char *) into numbers (int)*/
int	ft_atoi(char *str, int *flag)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		sign = signhandle(str[i], sign);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || res * sign > INT_MAX || res * sign < INT_MIN)
		*flag += 1;
	if (res * sign == INT_MIN)
		return (INT_MIN);
	return (res * sign);
}

/*Sets memory for the given block with the given int (Ex : 0)*/
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*pstr;
	size_t			i;

	pstr = (unsigned char *)s;
	i = 0;
	while (n)
	{
		pstr[i] = c;
		i++;
		n--;
	}
	return (s);
}
