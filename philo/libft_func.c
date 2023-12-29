/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metyasar <metyasar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:18:20 by metyasar          #+#    #+#             */
/*   Updated: 2023/12/25 17:07:46 by metyasar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *a)
{
	int		i;
	long	number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while (a[i])
	{
		number = (a[i] - 48) + (number * 10);
		if (number > 2147483647 || number < -2147483648)
			return (3);
		i++;
	}
	number = number * sign;
	return (number);
}

int	ft_error(t_data *data)
{
	printf("ERROR!\n");
	return (2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((unsigned char)*s1 == (unsigned char)*s2 && *s1 != 0 && n-- > 1)
	{
		s1++;
		s2++;
	}
	if ((unsigned char)*s1 == (unsigned char)*s2)
		return (0);
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}
