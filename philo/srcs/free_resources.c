/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:46:52 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/11 22:52:34 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_mutex(t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->number)
	{
		if (pthread_mutex_destroy(&info->fork[i]))
			return (1);
		i++;
	}
	free(info->fork);
	if (pthread_mutex_destroy(&info->key))
		return (1);
	return (0);
}

int	free_resources(t_philo *philo, t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->number)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (1);
		i++;
	}
	if (free_mutex(info))
		return (1);
	free(philo);
	return (0);
}
