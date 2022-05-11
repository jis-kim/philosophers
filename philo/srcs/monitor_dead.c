/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:08:21 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/11 22:54:28 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_full(t_philo *p, t_philo_info *info)
{
	if (!p->already_full && p->eat_count == p->info->must_eat_count)
	{
		p->already_full = 1;
		p->info->full_philo++;
	}
	if (info->full_philo == info->number)
	{
		info->dead_flag = 1;
		return (1);
	}
	return (0);
}

static int	check_dead(t_philo *p, t_philo_info *info, time_t now)
{
	if (p->last_eat_time + info->time_to_die < now)
	{
		printf("%ld \033[34m%d \033[1;31mis died\n\033[0m", now, p->index);
		info->dead_flag = 1;
		return (1);
	}
	return (0);
}

void	monitor_dead(t_philo *philo, t_philo_info *info)
{
	int		i;
	time_t	now;

	i = 0;
	now = 0;
	while (1)
	{
		if (i == info->number)
			i = 0;
		pthread_mutex_lock(&(info->key));
		now = get_passed_time(info->start_time);
		if (check_dead(&philo[i], info, now) || check_full(&philo[i], info))
		{
			pthread_mutex_unlock(&(info->key));
			return ;
		}
		pthread_mutex_unlock(&(info->key));
		i++;
		usleep(100);
	}
}
