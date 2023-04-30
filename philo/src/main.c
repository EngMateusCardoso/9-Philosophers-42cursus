/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:25:02 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/29 18:26:01 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork_and_lock_print(t_philo_env *philo_env)
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
}

void	init_philosopher(t_philo	*philos, t_philo_env *philo_env)
{
	int		index;

	index = 0;
	while (index < philo_env->philo_nbr)
	{
		philos[index].id = index + 1;
		philos[index].eat_count = 0;
		philos[index].last_eat = 0; // get_time();
		philos[index].left_fork = &philo_env->forks[index];
		philos[index].right_fork = &philo_env->forks[(index + 1) \
			% philo_env->philo_nbr];
		philos[index].philo_env = philo_env;
		index++;
	}
}

void	*monitor(void *arg)
{
	t_philo		*philos;
	int			index;
	int			stop;

	philos = (t_philo *)arg;
	stop = 1;
	while (stop)
	{
		index = 0;
		while (index < philos->philo_env->philo_nbr)
		{
			if (philos[index].eat_count == philos->philo_env->must_eat)
				stop = 0;
			index++;
		}
	}
	return (NULL);
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

void	run_philos(t_philo_env *philo_env)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * philo_env->philo_nbr);
	init_philosopher(philos, philo_env);
	run_dinner(philos, philo_env);
	finish_dinner(philos, philo_env);
}

int	main(int argc, char **argv)
{
	t_philo_env	philo_env;

	if (!check_args(argc, argv) || !init_philo_env(argc, argv, &philo_env))
		return (1);
	init_fork_and_lock_print(&philo_env);
	run_philos(&philo_env);
	write(1, "Dinner is over\n", 15);
	return (0);
}
