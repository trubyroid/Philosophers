/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 20:31:39 by truby             #+#    #+#             */
/*   Updated: 2021/09/08 01:19:36 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*officiant(t_ph *ph)
{
	int	i;

	i = 0;
	while (i != ph->all->philo_number)
	{
		if (ph->meal == ph->all->number_of_times_each_philosopher_must_eat
			&& ph->full == 0)
		{
			ph->full = 1;
			i++;
		}
		ph = ph->next_ph;
	}
	return (freeshing(ph));
}

void	*monitor(void *ph)
{
	unsigned long	life;
	unsigned long	now;

	while (1)
	{
		if (((t_ph *)ph)->all->number_of_times_each_philosopher_must_eat != -1)
		{
			if (((t_ph *)ph)->meal
				== ((t_ph *)ph)->all->number_of_times_each_philosopher_must_eat)
				return (officiant(ph));
		}
		life = get_time() - ((t_ph *)ph)->last_eat;
		if (life >= ((t_ph *)ph)->all->time_to_die)
		{
			if (pthread_mutex_lock(&g_mutexes
					[((t_ph *)ph)->all->philo_number]) != 0)
				error_func("Error of mutex.");
			now = get_time();
			printf("%lu %i %s\n", (now - ((t_ph *)ph)->all->start_time),
				 ((t_ph *)ph)->id, "is died");
			return (freeshing((t_ph *)ph));
		}
		ph = ((t_ph *)ph)->next_ph;
	}
	return (NULL);
}

void	*philo(void *ph)
{
	((t_ph *)ph)->last_eat = get_time();
	pthread_detach(g_streams[((t_ph *)ph)->id - 1]);
	if (((t_ph *)ph)->id % 2 == 0 && ((t_ph *)ph)->all->take_a_forks
		<= ((t_ph *)ph)->all->philo_number / 2)
		usleep(100);
	while (1)
		ontogenesis((t_ph *)ph);
	return (NULL);
}

void	ontogenesis(t_ph *ph)
{
	if (pthread_mutex_lock(&g_mutexes[ph->right_fork]) != 0)
		error_func("Error of mutex.\n");
	write_a_state(ph, "has taken a fork");
	if (pthread_mutex_lock(&g_mutexes[ph->left_fork]) != 0)
		error_func("Error of mutex.\n");
	write_a_state(ph, "has taken a fork");
	ph->last_eat = get_time();
	ph->meal++;
	if (ph->all->take_a_forks < 100)
		ph->all->take_a_forks++;
	write_a_state(ph, "is eating");
	my_usleep(ph->all->time_to_eat);
	if (pthread_mutex_unlock(&g_mutexes[ph->right_fork]) != 0)
		error_func("Error of mutex.\n");
	if (pthread_mutex_unlock(&g_mutexes[ph->left_fork]) != 0)
		error_func("Error of mutex.\n");
	write_a_state(ph, "is sleeping");
	my_usleep(ph->all->time_to_sleep);
	write_a_state(ph, "is thinking");
}
