/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dead_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:08:21 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/17 17:23:39 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_full(t_philo *p)
{
	if (p->eat_count == p->info->must_eat_count)
		sem_post(p->info->fin);
}

static void	check_dead(t_philo *p, time_t now)
{
	int	i;

	i = 0;
	if (p->last_eat_time + p->info->time_to_die < now)
	{
		sem_wait(p->info->key); //0
		while (i < p->info->number)
		{
			sem_post(p->info->fin);
			i++;
		}
		printf("%ld \033[34m%d \033[1;31mis died\033[0m\n", now, p->index);
		kill(0, SIGINT);
		sem_post(p->info->key);
		exit(1);
	}
}

void	*monitor_dead(void *philo)
{
	time_t	now;
	t_philo	*p;

	now = 0;
	p = (t_philo *)philo;
	while (1)
	{
		now = get_passed_time(p->info->start_time);
		check_dead(p, now);
		check_full(p);
		usleep(100);
	}
}
