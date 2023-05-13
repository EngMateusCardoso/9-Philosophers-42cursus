/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:27:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/05/13 13:08:47 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo		*philos;
	int			i;
	int			eat_count_sum;

	philos = (t_philo *)arg;
	i = 0;
	while (!get_dinner_over(philos))
	{
		if (i >= philos->philo_env->philo_nbr)
			i = 0;
		if (get_time(philos->philo_env->start_time)
			- get_last_eat(&(philos[i])) > philos->philo_env->time_to_die)
			set_dinner_over(philos, i);
		if (philos->philo_env->must_eat_goal >= 0)
			all_philos_ate_enough(philos, i, &eat_count_sum);
		i++;
		usleep(4);
	}
	return (NULL);
}

void	set_dinner_over(t_philo *philos, int i)
{
	pthread_mutex_lock(&(philos->philo_env->lock_print));
	printf("%ld %d died\n",
		get_time(philos->philo_env->start_time), philos[i].name);
	pthread_mutex_lock(&(philos->philo_env->lock_dinner_over));
	philos->philo_env->dinner_over = 1;
	pthread_mutex_unlock(&(philos->philo_env->lock_dinner_over));
	pthread_mutex_unlock(&(philos->philo_env->lock_print));
}

void	all_philos_ate_enough(t_philo *philos, int i, int *eat_count_sum)
{
	pthread_mutex_lock(&(philos[i].lock_eat_count));
	*eat_count_sum += philos[i].eat_count;
	pthread_mutex_unlock(&(philos[i].lock_eat_count));
	if (i == philos->philo_env->philo_nbr - 1)
	{
		if (*eat_count_sum >= philos->philo_env->must_eat_goal)
		{
			pthread_mutex_lock(&(philos->philo_env->lock_print));
			printf("All philosophers ate enough\n");
			pthread_mutex_lock(&(philos->philo_env->lock_dinner_over));
			philos->philo_env->dinner_over = 1;
			pthread_mutex_unlock(&(philos->philo_env->lock_dinner_over));
			pthread_mutex_unlock(&(philos->philo_env->lock_print));
		}
		*eat_count_sum = 0;
	}
}
