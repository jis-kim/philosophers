/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:39:05 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/09 21:39:01 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(int index, t_philo *philo, t_philo_info *info)
{
	philo->index = index;
	philo->info = info;
	philo->last_eat_time = info->start_time;
	philo->eat_count = 0;
	if (index == 1)
	{
		philo->left = &info->fork[0];
		philo->right = &info->fork[info->number - 1];
	}
	else
	{
		philo->left = &info->fork[index - 1];
		philo->right = &info->fork[index - 2];
	}
	return (0);
}

pthread_mutex_t	*init_forks(int number)
{
	int				i;
	pthread_mutex_t	*fork;

	i = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number);
	if (!fork)
		return (NULL);
	while (i < number)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (NULL);
		i++;
	}
	return (fork);
}
