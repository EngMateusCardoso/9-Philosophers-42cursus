/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:27:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/30 16:00:29 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philos_ate_enough(t_philo *philos, int i, int *eat_count_sum)
{
	if (philos->philo_env->must_eat == -1 || i >= philos->philo_env->philo_nbr)
		eat_count_sum = 0;
	else
	{
		*eat_count_sum += philos[i].eat_count;
		if (*eat_count_sum >= philos->philo_env->philo_nbr
			* philos->philo_env->must_eat)
		{
			pthread_mutex_lock(&(philos->philo_env->lock_print));
			printf("All philosophers ate enough\n");
			return (1);
		}
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo		*philos;
	int			i;
	int			stop;
	int			eat_count_sum;

	philos = (t_philo *)arg;
	stop = 0;
	i = 0;
	while (!stop)
	{
		if (i >= philos->philo_env->philo_nbr)
			i = 0;
		if (get_time(philos->philo_env->start_time)
			- philos[i].last_eat > philos->philo_env->time_to_die / 1000)
		{
			pthread_mutex_lock(&(philos->philo_env->lock_print));
			printf("%ld %d died\n",
				get_time(philos->philo_env->start_time), philos[i].id);
			stop = 1;
		}
		i++;
		if (all_philos_ate_enough(philos, i, &eat_count_sum))
			stop = 1;
	}
	return (NULL);
}
