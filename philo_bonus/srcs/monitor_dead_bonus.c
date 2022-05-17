/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dead_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:08:21 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/17 21:06:04 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_full(t_philo *p)
{
	sem_wait(p->info->key);
	if (p->eat_count == p->info->must_eat_count)
		sem_post(p->info->fin);
	sem_post(p->info->key);
}

static void	check_dead(t_philo *p)
{
	int		i;
	time_t	now;

	i = 0;
	sem_wait(p->info->key);
	now = get_passed_time(p->info->start_time);
	if (p->last_eat_time + p->info->time_to_die < now)
	{
		printf("%ld \033[34m%d \033[1;31mis died\033[0m\n", now, p->index);
		while (i < p->info->number)
		{
			sem_post(p->info->fin);
			i++;
		}
		exit(1);
	}
	sem_post(p->info->key);
}

void	*monitor_dead(void *philo)
{
	time_t	now;
	t_philo	*p;

	now = 0;
	p = (t_philo *)philo;
	while (1)
	{
		check_dead(p);
		check_full(p);
		usleep(100);
	}
}
