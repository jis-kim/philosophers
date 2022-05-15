/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Cated: 2022/05/01 21:07:35 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/13 15:45:58 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	do_one_routine(t_philo *p)
{
	take_fork(p);
	while (1)
	{
		sem_wait(p->info->key);
		if (p->info->dead_flag)
		{
			sem_post(p->info->key);
			sem_post(p->info->fork);
			return ;
		}
		sem_post(p->info->key);
		usleep(100);
	}
}

static int	do_routine(t_philo *p)
{
	int	ret;

	ret = philo_eat(p);
	if (ret == SUCCESS)
	{
		sem_wait(p->info->key);
		p->eat_count++;
		sem_post(p->info->key);
	}
	if (ret != ONE_FORK_DEAD)
		sem_post(p->info->fork);
	sem_post(p->info->fork);
	if (ret)
	{
		sem_post(p->info->key);
		return (1);
	}
	if (philo_sleep(p) || philo_think(p))
	{
		sem_post(p->info->key);
		return (1);
	}
	return (0);
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
	sem_wait(p->info->key);
	sem_post(p->info->key);
	if (p->index % 2 == 0)
		usleep((p->info->time_to_eat / 2) * 1000);
	while (!do_routine(p))
		;
	return (NULL);
}
