/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:05:50 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/11 22:59:06 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *p, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&(p->info->key));
	if (p->info->dead_flag)
		return (1);
	printf("%ld \033[34m%d \033[33mhas taken a fork\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	pthread_mutex_unlock(&(p->info->key));
	return (0);
}

int	philo_eat(t_philo *p)
{
	time_t	now;

	if (take_fork(p, p->left))
		return (ONE_FORK_DEAD);
	if (take_fork(p, p->right))
		return (TWO_FORK_DEAD);
	pthread_mutex_lock(&(p->info->key));
	if (p->info->dead_flag)
		return (TWO_FORK_DEAD);
	printf("%ld \033[34m%d \033[35mis eating\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	now = get_passed_time(p->info->start_time);
	p->last_eat_time = now;
	pthread_mutex_unlock(&(p->info->key));
	while (get_passed_time(p->info->start_time) < p->info->time_to_eat + now)
	{
		pthread_mutex_lock(&(p->info->key));
		if (p->info->dead_flag)
			return (TWO_FORK_DEAD);
		pthread_mutex_unlock(&(p->info->key));
		usleep(100);
	}
	p->eat_count++;
	return (SUCCESS);
}

int	philo_sleep(t_philo *p)
{
	time_t	now;

	pthread_mutex_lock(&(p->info->key));
	if (p->info->dead_flag)
		return (1);
	printf("%ld \033[34m%d \033[36mis sleeping\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	pthread_mutex_unlock(&(p->info->key));
	now = get_passed_time(p->info->start_time);
	while (get_passed_time(p->info->start_time) < p->info->time_to_sleep + now)
	{
		pthread_mutex_lock(&(p->info->key));
		if (p->info->dead_flag)
			return (1);
		pthread_mutex_unlock(&(p->info->key));
		usleep(100);
	}
	return (0);
}

int	philo_think(t_philo *p)
{
	pthread_mutex_lock(&(p->info->key));
	if (p->info->dead_flag)
		return (1);
	printf("%ld \033[34m%d \033[0mis thinking\n",
		get_passed_time(p->info->start_time), p->index);
	pthread_mutex_unlock(&(p->info->key));
	return (0);
}
