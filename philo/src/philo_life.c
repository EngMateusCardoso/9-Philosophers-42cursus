/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:29:11 by matcardo          #+#    #+#             */
/*   Updated: 2023/05/01 19:23:59 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1 && philo->id != philo->philo_env->philo_nbr)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	printf("%ld %d has taken a fork\n",
		get_time(philo->philo_env->start_time), philo->id);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	printf("%ld %d is eating\n", get_time(philo->philo_env->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
	philo->last_eat = get_time(philo->philo_env->start_time);
	if (philo->eat_count < philo->philo_env->must_eat)
		philo->eat_count++;
	usleep(philo->philo_env->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	printf("%ld %d is sleeping\n", get_time(philo->philo_env->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
	usleep(philo->philo_env->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	printf("%ld %d is thinking\n", get_time(philo->philo_env->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
