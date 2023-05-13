/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:24:55 by matcardo          #+#    #+#             */
/*   Updated: 2023/05/13 12:07:34 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_dinner_over(t_philo *philo)
{
	int	dinner_over;

	pthread_mutex_lock(&(philo->philo_env->lock_dinner_over));
	dinner_over = philo->philo_env->dinner_over;
	pthread_mutex_unlock(&(philo->philo_env->lock_dinner_over));
	return (dinner_over);
}

int	get_last_eat(t_philo *philo)
{
	int	last_eat;

	pthread_mutex_lock(&(philo->lock_last_eat));
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&(philo->lock_last_eat));
	return (last_eat);
}
