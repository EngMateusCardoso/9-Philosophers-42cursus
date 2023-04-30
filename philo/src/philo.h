/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:24:57 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/29 18:38:17 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo_env
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	suseconds_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_print;
	pthread_t		*philo_threads;
	pthread_t		thread_monitor;
}	t_philo_env;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo_env		*philo_env;
}	t_philo;

int		check_args(int argc, char **argv);
int		init_philo_env(int argc, char **argv, t_philo_env *philo_env);
int		ft_atoi(const char *nptr);
void	*philo_life(void *arg);
long	get_timestamp(long start_time);

#endif
