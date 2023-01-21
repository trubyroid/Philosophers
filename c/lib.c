/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 21:16:31 by truby             #+#    #+#             */
/*   Updated: 2021/09/08 01:18:19 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i = i + 1;
	return (i);
}

unsigned long	ft_atoi_ph(char *str)
{
	unsigned long				i;
	unsigned long				b;

	if (str == NULL)
		return (0);
	i = -1;
	b = 0;
	while (ft_isdigit(str[++i]) == 1)
	{
		b = b * 10 + (str[i] - '0');
		if (b > 420000000)
			error_func("Invalid argument.");
	}
	return (b);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

void	write_a_state(t_ph *ph, char *str)
{
	unsigned long	now;

	now = get_time();
	if (pthread_mutex_lock(&g_mutexes[ph->all->philo_number]) != 0)
		error_func("Error of mutex.\n");
	printf("%lu %i %s\n", (now - ph->all->start_time), ph->id, str);
	if (pthread_mutex_unlock(&g_mutexes[ph->all->philo_number]) != 0)
		error_func("Error of mutex.\n");
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	now;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (now);
}
