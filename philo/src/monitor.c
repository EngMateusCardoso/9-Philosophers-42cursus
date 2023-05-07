/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:27:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/05/06 22:31:32 by matcardo         ###   ########.fr       */
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
	while (!philos->philo_env->dinner_over)
	{
		if (i >= philos->philo_env->philo_nbr)
			i = 0;
		if (get_time(philos->philo_env->start_time)
			- philos[i].last_eat > philos->philo_env->time_to_die)
		{
			pthread_mutex_lock(&(philos->philo_env->lock_print));
			printf("%ld %d died\n",
				get_time(philos->philo_env->start_time), philos[i].name);
			philos->philo_env->dinner_over = 1;
			pthread_mutex_unlock(&(philos->philo_env->lock_print));
		}
		if (philos->philo_env->must_eat != -1)
			all_philos_ate_enough(philos, i, &eat_count_sum);
		i++;
	}
	return (NULL);
}

void	all_philos_ate_enough(t_philo *philos, int i, int *eat_count_sum)
{
	*eat_count_sum += philos[i].eat_count;
	if (i == philos->philo_env->philo_nbr - 1)
	{
		if (*eat_count_sum >= philos->philo_env->philo_nbr \
		* philos->philo_env->must_eat)
		{
			pthread_mutex_lock(&(philos->philo_env->lock_print));
			printf("All philosophers ate enough\n");
			philos->philo_env->dinner_over = 1;
			pthread_mutex_unlock(&(philos->philo_env->lock_print));
		}
		*eat_count_sum = 0;
	}
}
