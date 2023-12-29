/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metyasar <metyasar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:42:01 by metyasar          #+#    #+#             */
/*   Updated: 2023/12/24 14:47:44 by metyasar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_create(t_data *data, int ac)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->arguments[0]);
	if (!data->philo)
		return (1);
	data->is_dead = 0;
	while (i < data->arguments[0])
	{
		data->philo[i].data = data;
		data->philo[i].id = (i + 1);
		data->philo[i].dietime = data->arguments[1];
		data->philo[i].eattime = data->arguments[2];
		data->philo[i].sleeptime = data->arguments[3];
		data->philo[i].eat_counter = 0;
		if (ac == 6)
			data->philo[i].hmtimetoeat = data->arguments[4];
		else
			data->philo[i].hmtimetoeat = -1;
		i++;
	}
	return (0);
}

int	mutex_create(t_data *data)
{
	pthread_mutex_t	*frk;
	pthread_mutex_t	*time;
	int				i;

	i = -1;
	frk = malloc(sizeof(pthread_mutex_t) * data->arguments[0]);
	time = malloc(sizeof(pthread_mutex_t) * data->arguments[0]);
	if (!frk || !time)
		return (1);
	while (++i < data->arguments[0])
	{
		data->philo[i].own_fork_l = &frk[i];
		data->philo[i].time_for_philo_mutex = &time[i];
	}
	i = -1;
	while (++i < data->arguments[0])
	{
		if (i == (data->arguments[0] - 1))
			data->philo[i].fork_r = data->philo[0].own_fork_l;
		else
			data->philo[i].fork_r = data->philo[i + 1].own_fork_l;
	}
	return (0);
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->arguments[0]))
	{
		if (pthread_mutex_init(data->philo[i].own_fork_l, NULL))
			return (1);
		if (pthread_mutex_init(data->philo[i].time_for_philo_mutex, NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->common_mut, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mut, NULL))
		return (1);
	if (pthread_mutex_init(&data->eat_counter_mutex, NULL))
		return (1);
	return (0);
}

int	thread_push(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arguments[0])
	{
		if (pthread_create(&data->philo[i].thread,
				NULL, (void *)loop, &data->philo[i]))
			return (1);
		usleep(100);
		i += 2;
	}
	i = 1;
	while (i < data->arguments[0])
	{
		if (pthread_create(&data->philo[i].thread,
				NULL, (void *)loop, &data->philo[i]))
			return (1);
		usleep(100);
		i += 2;
	}
	return (0);
}

int	init_stack(t_data *data, char **av, int ac)
{
	int	i;

	i = 1;
	data->arguments = malloc(sizeof(int) * ac);
	if (!data->arguments)
		return (1);
	while (i < ac)
	{
		data->arguments[i - 1] = ft_atoi(av[i]);
		i++;
	}
	if (philo_create(data, ac))
		return (1);
	if (mutex_create(data))
		return (1);
	if (mutex_init(data))
		return (0);
	if (thread_push(data))
		return (1);
	return (0);
}
