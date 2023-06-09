/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:24:57 by matcardo          #+#    #+#             */
/*   Updated: 2023/05/13 14:25:32 by matcardo         ###   ########.fr       */
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
	int				must_eat_goal;
	long			start_time;
	long			start_time_thread;
	int				dinner_over;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_print;
	pthread_t		*philo_threads;
	pthread_t		thread_monitor;
	pthread_mutex_t	lock_dinner_over;
}	t_philo_env;

typedef struct s_philo
{
	int				id;
	int				name;
	int				eat_count;
	long			last_eat;
	int				is_only_one;
	int				philo_time_to_eat;
	int				philo_time_to_sleep;
	int				philo_must_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo_env		*philo_env;
	pthread_mutex_t	lock_eat_count;
	pthread_mutex_t	lock_last_eat;
}	t_philo;

int		check_args(int argc, char **argv);
size_t	ft_strlen(const char *s);
int		is_number(char *str);
int		init_philo_env(int argc, char **argv, t_philo_env *philo_env);
void	init_fork_and_locks(t_philo_env *philo_env);
void	finish_fork_and_locks(t_philo_env *philo_env);
void	run_philos(t_philo_env *philo_env);
void	init_philosopher(t_philo *philos, t_philo_env *philo_env);
void	run_dinner(t_philo	*philos, t_philo_env *philo_env);
void	finish_dinner(t_philo	*philos, t_philo_env *philo_env);
void	*philo_life(void *arg);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*monitor(void *arg);
void	set_dinner_over(t_philo *philos, int i);
void	all_philos_ate_enough(t_philo *philos, int i, int *eat_count_sum);
long	get_time(long start_time);
int		ft_atoi(const char *nptr);
void	*one_philo(t_philo	*philo);
int		get_dinner_over(t_philo *philo);
int		get_last_eat(t_philo *philo);

#endif
