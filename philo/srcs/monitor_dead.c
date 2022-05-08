/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:08:21 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/09 01:19:38 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo, time_t now)
{
	if (philo->last_eat_time + philo->info->time_to_die < now)
	{
		philo->info->dead_flag = 1;
		return (1);
	}
	return (0);
}

void	monitor_dead(t_philo *philo, t_philo_info *info)
{
	int i;
	time_t	now;

	i = 0;
	now = 0;
	while (1)
	{
		if (i == info->number)
			i = 0;
		now = get_passed_time(info->start_time);
		pthread_mutex_lock(&(info->print));
		if (check_dead(&philo[i], now))
		{
			printf("%ld %d \033[31mis died\n\033[0m", now, info->dead_flag);
			pthread_mutex_unlock(&(info->print));
			break;
		}
		pthread_mutex_unlock(&(info->print));
		i++;
		usleep(200);
	}
}
