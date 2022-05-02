/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:29:57 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/03 03:17:38 by jiskim           ###   ########.fr       */
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

long	get_time_ms(void)
{
	struct timeval tv;
	long time_now;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time_now = tv.tv_sec * 1000000 + tv.tv_usec;
	//printf("%ld\n", time_now);
	return (time_now);
}


long	get_passed_time(long start_time)
{
	//printf("%ld %ld\n", get_time_ms(), start_time);
	return ((get_time_ms() - start_time) / 10000);
}
