/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metyasar <metyasar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:04:54 by metyasar          #+#    #+#             */
/*   Updated: 2023/12/22 16:55:35 by metyasar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_food(t_philo *philo)
{
	pthread_mutex_lock(philo->time_for_philo_mutex);
	philo->last_eat_time = ft_get_time();
	if (write_func(philo, "is eating\n"))
		return (1);
	pthread_mutex_lock(&philo->data->eat_counter_mutex);
	philo->eat_counter++;
	pthread_mutex_unlock(&philo->data->eat_counter_mutex);
	if (ft_is_full(philo))
	{
		pthread_mutex_unlock(philo->time_for_philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->time_for_philo_mutex);
	ft_wait(ft_get_time(), philo->data->arguments[2]);
	pthread_mutex_unlock(philo->own_fork_l);
	pthread_mutex_unlock(philo->fork_r);
	return (0);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	if (write_func(philo, "has taken a fork!\n"))
		return (1);
	pthread_mutex_lock(philo->own_fork_l);
	if (write_func(philo, "has taken a fork!\n"))
		return (1);
	if (eat_food(philo))
		return (1);
	return (0);
}

int	write_func(t_philo *philo, char *status)
{
	t_time	now;

	now = ft_get_time() - philo->time;
	pthread_mutex_lock(&philo->data->common_mut);
	if (!ft_strncmp(status, "is dead\n", 8))
	{
		printf("%llu: philo %d %s", now, philo->id, status);
		pthread_mutex_unlock(&philo->data->death_mut);
		return (1);
	}
	if (death_control(philo))
		return (1);
	printf("%llu: philo %d %s", now, philo->id, status);
	pthread_mutex_unlock(&philo->data->common_mut);
	return (0);
}

int	sleepfunc(t_philo *philo)
{
	if (write_func(philo, "is sleeping\n"))
		return (1);
	ft_wait(ft_get_time(), philo->data->arguments[3]);
	if (write_func(philo, "is thinking\n"))
		return (1);
	return (0);
}

void	*loop(t_philo *philo)
{
	pthread_mutex_lock(philo->time_for_philo_mutex);
	philo->time = ft_get_time();
	philo->last_eat_time = philo->time;
	pthread_mutex_unlock(philo->time_for_philo_mutex);
	while (1)
	{
		if (take_fork(philo))
			break ;
		if (sleepfunc(philo))
			break ;
	}
	return (NULL);
}
