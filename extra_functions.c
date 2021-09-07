/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 19:06:59 by truby             #+#    #+#             */
/*   Updated: 2021/09/08 01:18:00 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_func_int(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (1);
}

void	*error_func(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (NULL);
}

void	my_usleep(unsigned long time)
{
	unsigned long	now;

	now = get_time();
	while (get_time() - now < time)
		usleep(100);
}

void	*freeshing(t_ph *ph)
{
	free(ph->all);
	ph->all = NULL;
	return (NULL);
}

int	freeshing_end(t_ph *ph)
{
	free(ph);
	free(g_streams);
	free(g_mutexes);
	return (0);
}
