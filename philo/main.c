/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metyasar <metyasar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:18:12 by metyasar          #+#    #+#             */
/*   Updated: 2023/12/25 17:07:50 by metyasar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_mutex_dest(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->common_mut))
		return (1);
	if (pthread_mutex_destroy(&data->eat_counter_mutex))
		return (1);
	if (pthread_mutex_destroy(&data->death_mut))
		return (1);
	while (i < data->arguments[0])
	{
		if (pthread_mutex_destroy(data->philo[i].own_fork_l))
			return (1);
		if (pthread_mutex_destroy(data->philo[i].time_for_philo_mutex))
			return (1);
		i++;
	}
	return (0);
}

int	philo_to_die(t_data *data, int i)
{
	int		check_dead;
	t_time	t;

	usleep(100);
	pthread_mutex_lock(data->philo[i].time_for_philo_mutex);
	t = ft_get_time();
	if ((int)(t - (data->philo[i].last_eat_time)) > data->arguments[1])
		check_dead = 1;
	else
		check_dead = 0;
	pthread_mutex_unlock(data->philo[i].time_for_philo_mutex);
	return (check_dead);
}

int	ft_dead_func(t_data *data)
{
	int	check_dead;
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->arguments[0])
		{
			check_dead = philo_to_die(data, i);
			pthread_mutex_lock(&data->death_mut);
			if (check_dead == 1)
			{
				data->is_dead = 1;
				return (write_func(&data->philo[i], "is dead\n"));
			}
			pthread_mutex_unlock(&data->death_mut);
		}
		if (ft_is_full(data->philo))
			break ;
	}
	return (0);
}

int	control(char **av, int ac)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == 3)
			return (1);
		else
			i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	if (argument_control(av, data) || (ac != 5 && ac != 6)
		|| argument_control2(av, ac) || control(av, ac))
	{
		if (ft_error(data) == 2)
			return (1);
	}
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (0);
		if (init_stack(data, av, ac))
			return (0);
		usleep(1000);
		if (ft_dead_func(data))
			return (0);
		if (thread_detach(data))
			return (1);
		if (ft_mutex_dest(data))
			return (1);
	}
}
