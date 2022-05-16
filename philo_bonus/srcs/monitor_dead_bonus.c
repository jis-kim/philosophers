/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dead_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:08:21 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/16 21:29:40 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//?????? 소통 어덯게하지
static int	check_full(t_philo *p)
{
	if (p->eat_count == p->info->must_eat_count)
		sem_post(p->info->full);
	return (0);
}

static int	check_dead(t_philo *p, time_t now)
{
	int	i;

	i = 0;
	sem_wait(p->info->key);
	if (p->last_eat_time + p->info->time_to_die < now)
	{
		printf("%ld \033[34m%d \033[1;31mis died\n\033[0m", now, p->index);
		// kill philosophers
		while (i < p->info->number)
		{
			if (i != p->index)
				kill(p->pid, SIGINT);
			i++;
		}
		exit(0); // 죽었따.
		sem_post(p->info->key);
		return (1);
	}
	sem_post(p->info->key);
	return (0);
}

void	*monitor_dead(void *philo)
{
	int		i;
	time_t	now;
	t_philo	*p;

	i = 0;
	now = 0;
	p = (t_philo *)philo;
	while (1)
	{
		now = get_passed_time(p->info->start_time);
		if (check_dead(p, now) || check_full(p))
			return (NULL);
		i++;
		usleep(100);
	}
}
