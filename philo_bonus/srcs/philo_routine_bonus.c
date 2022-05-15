/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:05:50 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/15 19:52:48 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_fork(t_philo *p)
{
	sem_wait(p->info->fork);
	sem_wait(p->info->key);
	if (p->info->dead_flag)
		return (1);
	printf("%ld \033[34m%d \033[33mhas taken a fork\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	sem_post(p->info->key);
	return (0);
}

int	philo_eat(t_philo *p)
{
	time_t	now;

	if (take_fork(p))
		return (ONE_FORK_DEAD);
	if (take_fork(p))
		return (TWO_FORK_DEAD);
	sem_wait(p->info->key);
	if (p->info->dead_flag)
		return (TWO_FORK_DEAD);
	printf("%ld \033[34m%d \033[35mis eating\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	now = get_passed_time(p->info->start_time);
	p->last_eat_time = now;
	sem_post(p->info->key);
	while (get_passed_time(p->info->start_time) < p->info->time_to_eat + now)
	{
		sem_wait(p->info->key);
		if (p->info->dead_flag)
			return (TWO_FORK_DEAD);
		sem_post(p->info->key);
		usleep(100);
	}
	return (SUCCESS);
}

int	philo_sleep(t_philo *p)
{
	time_t	now;

	sem_wait(p->info->key);
	if (p->info->dead_flag)
		return (1);
	printf("%ld \033[34m%d \033[36mis sleeping\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	sem_post(p->info->key);
	now = get_passed_time(p->info->start_time);
	while (get_passed_time(p->info->start_time) < p->info->time_to_sleep + now)
	{
		sem_wait(p->info->key);
		if (p->info->dead_flag)
			return (1);
		sem_post(p->info->key);
		usleep(100);
	}
	return (0);
}

int	philo_think(t_philo *p)
{
	sem_wait(p->info->key);
	if (p->info->dead_flag)
		return (1);
	printf("%ld \033[34m%d \033[0mis thinking\n",
		get_passed_time(p->info->start_time), p->index);
	sem_post(p->info->key);
	return (0);
}
