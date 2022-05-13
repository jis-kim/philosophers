/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:07:35 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/13 13:07:33 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_one_routine(t_philo *p)
{
	take_fork(p, p->left);
	while (1)
	{
		pthread_mutex_lock(&(p->info->key));
		if (p->info->dead_flag)
		{
			pthread_mutex_unlock(&(p->info->key));
			pthread_mutex_unlock(p->left);
			return ;
		}
		pthread_mutex_unlock(&(p->info->key));
		usleep(100);
	}
}

static int	do_routine(t_philo *p)
{
	int	ret;

	ret = philo_eat(p);
	if (ret == SUCCESS)
	{
		pthread_mutex_lock(&(p->info->key));
		p->eat_count++;
		pthread_mutex_unlock(&(p->info->key));
	}
	if (ret != ONE_FORK_DEAD)
		pthread_mutex_unlock(p->right);
	pthread_mutex_unlock(p->left);
	if (ret)
	{
		pthread_mutex_unlock(&(p->info->key));
		return (1);
	}
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
	if (p->info->number == 1)
	{
		do_one_routine(p);
		return (NULL);
	}
	pthread_mutex_lock(&(p->info->key));
	pthread_mutex_unlock(&(p->info->key));
	if (p->index % 2 == 0)
		usleep((p->info->time_to_eat / 2) * 1000);
	while (!do_routine(p))
		;
	return (NULL);
}
