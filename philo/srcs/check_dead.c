/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 03:58:45 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/06 04:41:02 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 죽었는지 살았는지 체크하는 함수
 */
int	check_dead(t_philo *philo, time_t now)
{
	if (philo->last_eat_time + philo->info->time_to_die < now)
	{
		philo->info->dead_flag = philo->index;
		return (1);
	}
	return (0);
}
