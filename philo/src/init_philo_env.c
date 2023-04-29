/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:39:56 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/16 13:39:20 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_env(int argc, char **argv, t_philo_env *philo_env)
{
	philo_env->philo_nbr = ft_atoi(argv[1]);
	philo_env->time_to_die = ft_atoi(argv[2]);
	philo_env->time_to_eat = ft_atoi(argv[3]);
	philo_env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_env->must_eat = ft_atoi(argv[5]);
	else
		philo_env->must_eat = -1;
	if (philo_env->philo_nbr == 0 || philo_env->time_to_die == 0
		|| philo_env->time_to_eat == 0 || philo_env->time_to_sleep == 0 ||
		philo_env->must_eat == 0)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	return (1);
}
