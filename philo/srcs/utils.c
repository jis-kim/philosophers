/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:29:57 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/11 03:54:34 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoui(char *argv)
{
	unsigned long long	num;
	int					length;

	num = 0;
	length = ft_strlen(argv);
	if (length > 10)
		return (-1);
	while (*argv)
	{
		if (*argv < '0' || *argv > '9')
			return (-1);
		num = num * 10 + (*argv - '0');
		if (num > 2147483647)
			return (-1);
		argv++;
	}
	return (num);
}

time_t	get_time_ms(void)
{
	struct timeval	tv;
	time_t			time_now;

	gettimeofday(&tv, NULL);
	time_now = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time_now);
}

time_t	get_passed_time(time_t start_time)
{
	return ((get_time_ms() - start_time) / 1000);
}
