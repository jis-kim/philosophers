/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:07:35 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/09 22:12:50 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	do_routine(t_philo *p, pthread_mutex_t *fst, pthread_mutex_t *snd)
{
	int	ret;

	ret = philo_eat(p, fst, snd);
	pthread_mutex_unlock(fst);
	if (ret != ONE_FORK_DEAD)
		pthread_mutex_unlock(snd);
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
	pthread_mutex_t	*fst;
	pthread_mutex_t	*snd;

	p = (t_philo *)philo;
	pthread_mutex_lock(&(p->info->key));
	if (p->index % 2)
	{
		fst = p->left;
		snd = p->right;
	}
	else
	{
		fst = p->right;
		snd = p->left;
	}
	pthread_mutex_unlock(&(p->info->key));
	while (!do_routine(p, fst, snd))
		;
	return (NULL);
}
