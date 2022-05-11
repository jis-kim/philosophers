/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:39:05 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/11 22:22:21 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->number)
	{
		philo[i].index = i + 1;
		philo[i].info = info;
		philo[i].last_eat_time = info->start_time;
		philo[i].eat_count = 0;
		philo[i].already_full = 0;
		if (i == 0)
		{
			philo[i].left = &info->fork[0];
			philo[i].right = &info->fork[info->number - 1];
		}
		else
		{
			philo[i].left = &info->fork[i];
			philo[i].right = &info->fork[i - 1];
		}
		i++;
	}
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
