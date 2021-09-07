/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 23:27:49 by truby             #+#    #+#             */
/*   Updated: 2021/09/08 01:19:09 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_ph	*left_fork_and_list(int i, t_all *arg, t_ph *ph)
{
	ph[i].last_eat = get_time();
	if (i < arg->philo_number - 1 || arg->philo_number == 1)
	{
		if (arg->philo_number == 1)
		{
			ph[i].next_ph = &ph[i];
			ph[i].left_fork = 0;
		}
		else
		{
			ph[i].next_ph = &ph[i + 1];
			ph[i].left_fork = i + 1;
		}
	}
	else
	{
		ph[i].next_ph = &ph[0];
		ph[i].left_fork = 0;
	}
	return (ph);
}

static t_ph	*init(t_all *arg)
{
	t_ph	*ph;
	int		i;

	ph = malloc(sizeof(t_ph) * (arg->philo_number));
	if (ph == NULL)
		return (error_func("Error of malloc.\n"));
	i = 0;
	while (i < arg->philo_number)
	{
		ph[i].all = arg;
		ph[i].meal = 0;
		ph[i].full = 0;
		ph[i].id = i + 1;
		ph[i].right_fork = i;
		left_fork_and_list(i, arg, ph);
		i++;
	}
	return (ph);
}

void	*start_threads(int i, int fl, t_all *arg, t_ph *ph)
{
	t_ph	*list;

	if (fl == 2)
		arg->start_time = get_time();
	if (fl == 1 || fl == 2)
	{
		while (i < arg->philo_number)
		{
			list = &ph[i];
			if (pthread_create(&g_streams[i],
					NULL, philo, (void *)list) != 0)
				return (error_func("Error of threads.\n"));
			i += 2;
		}
	}
	else
	{
		list = &ph[0];
		if (pthread_create(&g_streams[arg->philo_number],
				NULL, monitor, (void *)list) != 0)
			return (error_func("Error of threads.\n"));
		if (pthread_join(g_streams[arg->philo_number], NULL) != 0)
			return (error_func("Error of threads.\n"));
	}
	return (ph);
}

static int	start_func(t_all *arg, t_ph *ph)
{
	int	i;

	i = -1;
	while (++i < arg->philo_number + 1)
	{
		if (pthread_mutex_init(&g_mutexes[i], NULL) != 0)
			return (error_func_int("Error of mutex.\n"));
	}
	if (!start_threads(0, 2, arg, ph)
		|| !start_threads(1, 1, arg, ph)
		|| !start_threads(0, 3, arg, ph))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_all	*arg;
	t_ph	*ph;
	t_ph	*it;
	int		i;

	arg = check_n_parse(ac, av);
	if (arg == NULL)
		return (1);
	if (arg->number_of_times_each_philosopher_must_eat == 0)
		return (0);
	ph = init(arg);
	if (ph == NULL)
		return (1);
	g_streams = malloc(sizeof(pthread_t) * arg->philo_number + 1);
	g_mutexes = malloc(sizeof(pthread_mutex_t) * arg->philo_number + 1);
	if (g_mutexes == NULL || g_streams == NULL)
		return (error_func_int("Error of malloc.\n"));
	start_func(arg, ph);
	return (freeshing_end(ph));
}
