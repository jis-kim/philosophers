/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:07:35 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/09 21:36:07 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_action(void *philo)
{
	int				ret;
	t_philo			*p;
	pthread_mutex_t	*fst;
	pthread_mutex_t	*snd;

	p = (t_philo *)philo;
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
	while (1)
	{
		ret = philo_eat(p, fst, snd);
		if (ret)
		{
			pthread_mutex_unlock(&(p->info->key));
			pthread_mutex_unlock(fst);
			if (ret == 2)
				pthread_mutex_unlock(snd);
			return (NULL);
		}
		if (philo_sleep(p) || philo_think(p))
		{
			pthread_mutex_unlock(&(p->info->key));
			return (NULL);
		}
	}
}
