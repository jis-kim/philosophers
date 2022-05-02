/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:39:05 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/03 02:42:50 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(int index, t_philo *philo, t_philo_info *info)
{
	philo->index = index;
	philo->info = info;
	philo->last_eat_time = info->start_time;
	philo->eat_count = 0;
}

pthread_mutex_t	*init_forks(int number)
{
	int	i;
	pthread_mutex_t *fork;

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
