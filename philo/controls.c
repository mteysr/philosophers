/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metyasar <metyasar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:39:21 by metyasar          #+#    #+#             */
/*   Updated: 2023/12/21 12:02:09 by metyasar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argument_control(char **av, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	death_control(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mut);
	if (philo->data->is_dead == 1)
		return (1);
	pthread_mutex_unlock(&philo->data->death_mut);
	return (0);
}

int	argument_control2(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '0')
			return (1);
		i++;
	}
	return (0);
}
