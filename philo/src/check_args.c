/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:18:07 by matcardo          #+#    #+#             */
/*   Updated: 2023/04/03 08:42:49 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*(s + count))
		count++;
	return (count);
}

int	is_number(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	index;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments\n");
		return (0);
	}
	index = 1;
	while (argv[index])
	{
		if (ft_strlen(argv[index]) > 11 || !is_number(argv[index])
			|| ft_atoi(argv[index]) < 0)
		{
			printf("%dst argument isn't a positive int\n", index);
			return (0);
		}
		index++;
	}
	return (1);
}
