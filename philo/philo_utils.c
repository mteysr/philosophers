/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metyasar <metyasar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:34:51 by metyasar          #+#    #+#             */
/*   Updated: 2023/12/25 11:42:18 by metyasar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_full(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo[i].hmtimetoeat == -1)
		return (0);
	if (i < philo[i].data->arguments[0])
	{
		pthread_mutex_lock(&philo->data->eat_counter_mutex);
		if (philo->data->philo[i].eat_counter <= philo->data->arguments[4])
		{
			pthread_mutex_unlock(&philo->data->eat_counter_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->eat_counter_mutex);
	}
	return (1);
}

t_time	ft_get_time(void)
{
	struct timeval	tv;
	t_time			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	ft_wait(int p_time, int w_time)
{
	t_time	t;

	t = ft_get_time();
	while ((int)(t - p_time) < w_time)
	{
		usleep(100);
		t = ft_get_time();
	}
	return (0);
}

int	thread_detach(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arguments[0])
	{
		if (pthread_detach(data->philo[i].thread))
			return (1);
		i++;
	}
	return (0);
}
