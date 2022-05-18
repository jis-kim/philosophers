/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:07:35 by skim              #+#    #+#             */
/*   Updated: 2022/05/18 19:02:00 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	do_one_routine(t_philo *p)
{
	take_fork(p);
	while (1)
		usleep(100);
}

static void	do_routine(t_philo *p)
{
	philo_eat(p);
	sem_wait(p->info->key);
	p->eat_count++;
	sem_post(p->info->key);
	sem_post(p->info->fork);
	sem_post(p->info->fork);
	philo_sleep(p);
	philo_think(p);
}

void	*philo_action(void *philo)
{
	t_philo			*p;

	p = (t_philo *)philo;
	if (p->info->number == 1)
	{
		do_one_routine(p);
		return (NULL);
	}
	if (p->index % 2 == 0)
		usleep((p->info->time_to_eat / 2) * 1000);
	while (1)
		do_routine(p);
	return (NULL);
}
