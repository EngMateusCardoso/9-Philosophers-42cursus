/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:23:30 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/30 15:26:26 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_dinner(t_philo	*philos, t_philo_env *philo_env)
{
	int	index;

	index = 0;
	while (index < philo_env->philo_nbr)
	{
		pthread_join(philo_env->philo_threads[index], NULL);
		printf("Philosopher %d ate %d times\n", philos[index].id, \
			philos[index].eat_count);
		index++;
	}
}

void	run_dinner(t_philo	*philos, t_philo_env *philo_env)
{
	pthread_t	*philo_threads;
	pthread_t	thread_monitor;
	int			index;

	index = 0;
	philo_threads = malloc(sizeof(pthread_t) * philo_env->philo_nbr);
	while (index < philo_env->philo_nbr)
	{
		pthread_create(&philo_threads[index], NULL, &philo_life, \
			&philos[index]);
		index++;
	}
	pthread_create(&thread_monitor, NULL, &monitor, philos);
	philo_env->philo_threads = philo_threads;
	philo_env->thread_monitor = thread_monitor;
}

void	init_philosopher(t_philo	*philos, t_philo_env *philo_env)
{
	int		index;

	index = 0;
	while (index < philo_env->philo_nbr)
	{
		philos[index].id = index + 1;
		philos[index].eat_count = 0;
		philos[index].last_eat = 0;
		philos[index].left_fork = &philo_env->forks[index];
		philos[index].right_fork = &philo_env->forks[(index + 1) \
			% philo_env->philo_nbr];
		philos[index].philo_env = philo_env;
		index++;
	}
}

void	run_philos(t_philo_env *philo_env)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * philo_env->philo_nbr);
	init_philosopher(philos, philo_env);
	run_dinner(philos, philo_env);
	finish_dinner(philos, philo_env);
}
