/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:46:52 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/16 20:45:02 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int free_fork(t_philo_info *info)
{
	sem_close(info->fork);
	if (sem_unlink(FORK))
		return (1);
	return (0);
}

int free_resources(t_philo *philo, t_philo_info *info)
{
	while (waitpid(-1, NULL, 0) != -1)
		;
	if (free_fork(info))
		return (1);
	sem_close(info->key);
	if (sem_unlink(KEY))
		return (1);
	free(philo);
	return (0);
}
