/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 03:58:45 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/07 00:35:22 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 죽었는지 살았는지 체크하는 함수
 */
int	check_dead(t_philo *philo, time_t now)
{
	pthread_mutex_lock(&(philo->info->print));
	if (philo->last_eat_time + philo->info->time_to_die < now)
	{
		philo->info->dead_flag = philo->index; //철학자 번호로 setting
		pthread_mutex_unlock(&(philo->info->print));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->print));
	return (0);
}
