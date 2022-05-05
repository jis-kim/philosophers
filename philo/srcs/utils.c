/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:29:57 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/06 02:06:54 by jiskim           ###   ########.fr       */
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

time_t	get_time_ms(void)
{
	struct timeval tv;
	time_t time_now;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time_now = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time_now);
}


time_t	get_passed_time(time_t start_time)
{
	return ((get_time_ms() - start_time) / 1000);
}
