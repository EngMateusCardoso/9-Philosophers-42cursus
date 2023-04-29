/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:29:11 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/16 17:52:12 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	printf("%d is eating\n", philo->id);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
	usleep(philo->philo_env->time_to_eat * 1000);
	// philo->last_eat = get_time();
	philo->eat_count++;
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	printf("%d is sleeping\n", philo->id);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
	usleep(philo->philo_env->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	printf("%d is thinking\n", philo->id);
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
