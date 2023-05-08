/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:29:54 by matcardo          #+#    #+#             */
/*   Updated: 2023/05/08 10:19:28 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	result;

	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
		result = result * 10 + (*nptr++ - 48);
	if (result > 2147483647)
		return (-1);
	return (result);
}

long	get_time(long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
}

void	*one_philo(t_philo	*philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&(philo->philo_env->lock_print));
	if (!philo->philo_env->dinner_over)
		printf("%ld %d has taken a fork\n", \
			get_time(philo->philo_env->start_time), philo->name);
	pthread_mutex_unlock(&(philo->philo_env->lock_print));
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}
