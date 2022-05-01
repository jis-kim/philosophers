/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:39:05 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/01 19:40:51 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(int index, t_philo_info *info)
{
	info->number = index;
	if (info->fork == NULL)
		print_malloc_error();
}

void	init_forks(pthread_mutex_t *fork, t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->number)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}
