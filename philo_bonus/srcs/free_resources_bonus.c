/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:46:52 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/17 20:39:44 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	expire_sem(sem_t *sem, const char *sem_name)
{
	sem_close(sem);
	sem_unlink(sem_name);
}

void	free_resources(t_philo *philo, t_philo_info *info)
{
	sem_close(info->fork);
	sem_unlink(FORK);
	sem_close(info->key);
	sem_unlink(KEY);
	sem_close(info->fin);
	sem_unlink(FIN);
	if (philo)
		free(philo);
}
