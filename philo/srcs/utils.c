/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:29:57 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/01 23:26:22 by jiskim           ###   ########.fr       */
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
	time_now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_now);
}