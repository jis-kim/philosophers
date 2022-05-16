/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:46:52 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/15 22:36:04 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_fork(t_philo_info *info)
{
	if (sem_close(info->fork))
		return (1); // invalid sem descriptor
	sem_unlink(FORK);
	return (0);
}

int	free_resources(t_philo *philo, t_philo_info *info, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (waitpid(philo[i].pid))
			return (1);
		i++;
	}
	if (free_fork(info))
		return (1);
	sem_close(info->key);
	if (sem_unlink(KEY))
		return (1);
	free(philo);
	return (0);
}
