/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:07:35 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/11 04:08:58 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	do_routine(t_philo *p)
{
	int	ret;

	ret = philo_eat(p);
	if (ret != ONE_FORK_DEAD)
		pthread_mutex_unlock(p->right);
	pthread_mutex_unlock(p->left);
	if (ret)
	{
		pthread_mutex_unlock(&(p->info->key));
		return (1);
	}
	pthread_mutex_lock(&(p->info->key));
	if (p->eat_count == p->info->must_eat_count)
		p->info->full_philo++;
	pthread_mutex_unlock(&(p->info->key));
	if (philo_sleep(p) || philo_think(p))
	{
		pthread_mutex_unlock(&(p->info->key));
		return (1);
	}
	return (0);
}

void	*philo_action(void *philo)
{
	t_philo			*p;

	p = (t_philo *)philo;
	pthread_mutex_lock(&(p->info->key));
	pthread_mutex_unlock(&(p->info->key));
	if (p->index % 2 == 0)
		usleep((p->info->time_to_eat / 2) * 1000);
	while (!do_routine(p))
		;
	return (NULL);
}
