/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:25:02 by matcardo          #+#    #+#             */
/*   Updated: 2023/05/13 14:25:45 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_env	philo_env;

	if (!check_args(argc, argv) || !init_philo_env(argc, argv, &philo_env))
		return (1);
	init_fork_and_locks(&philo_env);
	run_philos(&philo_env);
	finish_fork_and_locks(&philo_env);
	write(1, "Dinner is over\n", 15);
	return (0);
}

int	init_philo_env(int argc, char **argv, t_philo_env *philo_env)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo_env->philo_nbr = ft_atoi(argv[1]);
	philo_env->time_to_die = ft_atoi(argv[2]);
	philo_env->time_to_eat = ft_atoi(argv[3]);
	philo_env->time_to_sleep = ft_atoi(argv[4]);
	philo_env->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo_env->start_time_thread = philo_env->start_time;
	if (argc == 6)
		philo_env->must_eat = ft_atoi(argv[5]);
	else
		philo_env->must_eat = -1;
	philo_env->must_eat_goal = philo_env->must_eat * philo_env->philo_nbr;
	if (philo_env->philo_nbr == 0 || philo_env->time_to_die == 0 \
		|| philo_env->time_to_eat == 0 || philo_env->time_to_sleep == 0 \
		|| philo_env->must_eat == 0)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	philo_env->dinner_over = 0;
	return (1);
}

void	init_fork_and_locks(t_philo_env *philo_env)
{
	int				index;

	index = 0;
	philo_env->forks = malloc(sizeof(pthread_mutex_t) * philo_env->philo_nbr);
	while (index < philo_env->philo_nbr)
	{
		pthread_mutex_init(&philo_env->forks[index], NULL);
		index++;
	}
	pthread_mutex_init(&philo_env->lock_print, NULL);
	pthread_mutex_init(&philo_env->lock_dinner_over, NULL);
}

void	finish_fork_and_locks(t_philo_env *philo_env)
{
	int	index;

	index = 0;
	while (index < philo_env->philo_nbr)
	{
		pthread_mutex_destroy(&philo_env->forks[index]);
		index++;
	}
	pthread_mutex_destroy(&philo_env->lock_print);
	pthread_mutex_destroy(&philo_env->lock_dinner_over);
	free(philo_env->forks);
}
