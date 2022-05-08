/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:07:35 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/09 01:43:12 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *p)
{
	time_t now;

	if (p->info->dead_flag)
		return (1);
	pthread_mutex_lock(&(p->info->print));
	printf("%ld %d is sleeping\n", get_passed_time(p->info->start_time), p->index);
	pthread_mutex_unlock(&(p->info->print));
	now = get_passed_time(p->info->start_time);
	while (get_passed_time(p->info->start_time) < p->info->time_to_sleep + now)
	{
		if (p->info->dead_flag)
			return (1);
		usleep(100);
	}
	return (0);
}

int	philo_think(t_philo *p)
{
	if (p->info->dead_flag)
		return (1);
	pthread_mutex_lock(&(p->info->print));
	printf("%ld %d is thinking\n", get_passed_time(p->info->start_time), p->index);
	pthread_mutex_unlock(&(p->info->print));
	if (p->info->dead_flag)
		return (1);
	return (0);
}

int	take_fork(t_philo *p, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (p->info->dead_flag)
	{
		pthread_mutex_unlock(fork);
		return (1);
	}
	pthread_mutex_lock(&(p->info->print));
	printf("%ld %d has taken a fork\n", get_passed_time(p->info->start_time), p->index);
	pthread_mutex_unlock(&(p->info->print));
	return (0);
}

int	philo_eat(t_philo *p, pthread_mutex_t *fst, pthread_mutex_t *snd)
{
	time_t	last_eat;

	if (take_fork(p, fst) || take_fork(p, snd))
		return (1);
	if (p->info->dead_flag)
	{
		pthread_mutex_unlock(fst);
		pthread_mutex_unlock(snd);
		return (1);
	}
	pthread_mutex_lock(&(p->info->print));
	printf("%ld %d is eating\n", get_passed_time(p->info->start_time), p->index);
	last_eat = get_passed_time(p->info->start_time);
	p->last_eat_time = last_eat;
	pthread_mutex_unlock(&(p->info->print));
	while (get_passed_time(p->info->start_time) < p->info->time_to_eat + last_eat)
	{
		if (p->info->dead_flag)
		{
			pthread_mutex_unlock(fst);
			pthread_mutex_unlock(snd);
			return (1);
		}
		usleep(100);
	}
	p->eat_count++;
	pthread_mutex_unlock(fst);
	pthread_mutex_unlock(snd);
	return (0);
}

void *philo_action(void *philo)
{
	int	ret;
	t_philo	*p;

	ret = 0;
	p = (t_philo *)philo;
	while (1)
	{
		if (p->index % 2)
			ret = philo_eat(p, p->left, p->right);
		else
			ret = philo_eat(p, p->right, p->left);
		if (ret)
			return (NULL);
		if (philo_sleep(p))
			return (NULL);
		if (philo_think(p))
			return (NULL);
	}
}
