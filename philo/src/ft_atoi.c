/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:36:07 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/03 08:37:06 by matcardo         ###   ########.fr       */
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
