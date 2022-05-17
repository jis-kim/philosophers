/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:05:50 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/17 21:07:59 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_philo *p)
{
	sem_wait(p->info->fork);
	sem_wait(p->info->key);
	printf("%ld \033[34m%d \033[33mhas taken a fork\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	sem_post(p->info->key);
}

void	philo_eat(t_philo *p)
{
	time_t	now;

	take_fork(p);
	take_fork(p);
	sem_wait(p->info->key);
	printf("%ld \033[34m%d \033[35mis eating\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	now = get_passed_time(p->info->start_time);
	sem_post(p->info->key);
	sem_wait(p->info->key);
	p->last_eat_time = now;
	sem_post(p->info->key);
	while (get_passed_time(p->info->start_time) < p->info->time_to_eat + now)
		usleep(100);
}

void	philo_sleep(t_philo *p)
{
	time_t	now;

	sem_wait(p->info->key);
	printf("%ld \033[34m%d \033[36mis sleeping\033[0m\n",
		get_passed_time(p->info->start_time), p->index);
	sem_post(p->info->key);
	now = get_passed_time(p->info->start_time);
	while (get_passed_time(p->info->start_time) < p->info->time_to_sleep + now)
		usleep(100);
}

void	philo_think(t_philo *p)
{
	sem_wait(p->info->key);
	printf("%ld \033[34m%d \033[0mis thinking\n",
		get_passed_time(p->info->start_time), p->index);
	sem_post(p->info->key);
}
