/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:27:13 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/30 15:38:19 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo		*philos;
	int			i;
	int			stop;

	philos = (t_philo *)arg;
	stop = 0;
	while (!stop)
	{
		i = 0;
		while (i < philos->philo_env->philo_nbr)
		{
			if (get_time(philos->philo_env->start_time)
				- philos[i].last_eat > philos->philo_env->time_to_die / 1000)
			{
				pthread_mutex_lock(&(philos->philo_env->lock_print));
				printf("%ld %d died\n",
					get_time(philos->philo_env->start_time), philos[i].id);
				stop = 1;
			}
			i++;
		}
	}
	return (NULL);
}
