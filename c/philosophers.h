/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 23:29:21 by truby             #+#    #+#             */
/*   Updated: 2021/09/08 01:19:44 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

// typedef pthread_mutex_t t_mutex;

pthread_mutex_t		*g_mutexes;

pthread_t			*g_streams;

typedef struct s_all
{
	int				i;
	int				take_a_forks;
	int				philo_number;
	unsigned long	start_time;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	number_of_times_each_philosopher_must_eat;
}				t_all;

typedef struct s_ph
{
	int				id;
	int				full;
	unsigned long	meal;
	int				left_fork;
	int				right_fork;
	unsigned long	last_eat;
	t_all			*all;
	struct s_ph		*next_ph;
}				t_ph;

int				main(int ac, char **av);
t_all			*check_n_parse(int ac, char **av);
void			*error_func(char *str);
void			*philo(void *arr);
void			*monitor(void *arr);
int				ft_strlen(char *str);
int				ft_isdigit(int c);
unsigned long	ft_atoi_ph(char *str);
char			*ft_itoa_ph(unsigned long n);
unsigned long	get_time(void);
void			write_a_state(t_ph *ph, char *str);
void			my_usleep(unsigned long time);
void			*officiant(t_ph *ph);
void			*start_threads(int i, int fl, t_all *arg, t_ph *ph);
void			ontogenesis(t_ph *ph);
void			*freeshing(t_ph *ph);
int				error_func_int(char *str);
int				freeshing_end(t_ph *ph);

#endif
