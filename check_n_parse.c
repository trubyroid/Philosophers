/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:19:33 by truby             #+#    #+#             */
/*   Updated: 2021/09/08 01:17:37 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*checker(int ac, char **av)
{
	int	i;
	int	j;

	j = 1;
	if (ac > 6 || ac < 4)
		error_func("Invalid number of arguments.\n");
	while (av[++j] != NULL)
	{
		i = -1;
		while (av[j][++i] != '\0')
		{
			if (j == 1 && i > 3)
				return (error_func("Invalid argument.\n"));
			if (j > 1 && i > 10)
				return (error_func("Invalid argument.\n"));
			if (!ft_isdigit(av[j][i]))
				return (error_func("Invalid argument.\n"));
		}
	}
	return (av[0]);
}

static t_all	*parser(char **av)
{
	t_all	*arg;

	arg = malloc(sizeof(t_all));
	arg->take_a_forks = 0;
	arg->philo_number = ft_atoi_ph(av[1]);
	if (arg->philo_number < 1 || arg->philo_number > 200)
		return (error_func("Invalid number of philosophers.\n"));
	arg->time_to_die = ft_atoi_ph(av[2]);
	arg->time_to_eat = ft_atoi_ph(av[3]);
	arg->time_to_sleep = ft_atoi_ph(av[4]);
	if (arg->time_to_sleep < 60 || arg->time_to_eat < 60
		 || arg->time_to_die < 60)
		return (error_func("Invalid argument.\n"));
	if (av[5] != NULL)
	{
		arg->number_of_times_each_philosopher_must_eat = ft_atoi_ph(av[5]);
		if (arg->number_of_times_each_philosopher_must_eat > 1000)
			return (error_func
				("Invalid number of times each philosopher must_eat.\n"));
	}
	else
		arg->number_of_times_each_philosopher_must_eat = -1;
	return (arg);
}

t_all	*check_n_parse(int ac, char **av)
{
	t_all	*arg;

	if (!checker(ac, av))
		return (NULL);
	arg = parser(av);
	if (arg == NULL)
		return (NULL);
	return (arg);
}