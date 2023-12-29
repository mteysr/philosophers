/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metyasar <metyasar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:18:23 by metyasar          #+#    #+#             */
/*   Updated: 2023/12/25 17:13:49 by metyasar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef unsigned long long	t_time;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				dietime;
	int				eattime;
	int				sleeptime;
	int				hmtimetoeat;
	t_time			time;
	t_time			last_eat_time;
	pthread_mutex_t	*own_fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*time_for_philo_mutex;
	pthread_t		thread;
	int				eat_counter;
}	t_philo;

typedef struct s_data
{
	int				*arguments;
	t_philo			*philo;
	int				is_dead;
	pthread_mutex_t	common_mut;
	pthread_mutex_t	death_mut;
	pthread_mutex_t	eat_counter_mutex;
}	t_data;

int		argument_control2(char **av, int ac);
int		ft_mutex_dest(t_data *data);
int		ft_strlen(char *str);
int		init_stack(t_data *data, char **av, int ac);
int		sleepfunc(t_philo *philo);
int		ft_wait(int p_time, int w_time);
int		mutex_init(t_data *data);
int		ft_atoi(char *a);
int		ft_error(t_data *data);
int		write_func(t_philo *philo, char *status);
void	*loop(t_philo *philo);
int		take_fork(t_philo *philo);
int		death_control(t_philo *philo);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		eat_food(t_philo *philo);
int		sleepfunc(t_philo *philo);
int		thread_detach(t_data *data);
int		argument_control(char **av, t_data *data);
int		ft_is_full(t_philo *philo);
t_time	ft_get_time(void);

#endif
