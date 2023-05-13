/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:29:11 by matcardo          #+#    #+#             */
/*   Updated: 2023/05/13 14:27:35 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->is_only_one)
		return (one_philo(philo));
	while (!get_dinner_over(philo))
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	if (!get_dinner_over(philo))
		printf("%ld %d has taken a fork\n",
			get_time(philo->philo_env->start_time_thread), philo->name);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	if (!get_dinner_over(philo))
		printf("%ld %d has taken a fork\n",
			get_time(philo->philo_env->start_time_thread), philo->name);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	if (!get_dinner_over(philo))
		printf("%ld %d is eating\n", \
		get_time(philo->philo_env->start_time_thread), philo->name);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
	pthread_mutex_lock(&(philo->lock_last_eat));
	philo->last_eat = get_time(philo->philo_env->start_time_thread);
	pthread_mutex_unlock(&(philo->lock_last_eat));
	pthread_mutex_lock(&(philo->lock_eat_count));
	if (philo->eat_count < philo->philo_must_eat)
		philo->eat_count++;
	pthread_mutex_unlock(&(philo->lock_eat_count));
	usleep(philo->philo_time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	if (!get_dinner_over(philo))
		printf("%ld %d is sleeping\n", \
		get_time(philo->philo_env->start_time_thread), philo->name);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
	usleep(philo->philo_time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	if (!get_dinner_over(philo))
		printf("%ld %d is thinking\n", \
			get_time(philo->philo_env->start_time_thread), philo->name);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
}
