/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/17 18:38:08 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int born_philosophers(t_philo *philo, t_philo_info *info)
{
	int i;
	pid_t pid;

	i = 0;
	while (i < info->number)
	{
		pid = fork();
		if (pid == -1)
			return (i);
		if (pid == 0)
		{
			pthread_create(&philo[i].thread, NULL, monitor_dead, &philo[i]);
			pthread_detach(philo[i].thread);
			philo_action(&philo[i]);
			return (-1);
		}
		philo[i].pid = pid;
		i++;
	}
	return (i);
}

int main(int argc, char **argv)
{
	t_philo_info philo_info;
	t_philo *philo;
	int ret;
	int i;

	if ((argc != 5 && argc != 6))
		return (print_error(ARG_ERROR));
	philo = NULL;
	ret = init_data(argc, argv, &philo, &philo_info);
	if (ret)
		return (print_error(ret));
	init_philo(philo, &philo_info);
	philo_info.start_time = get_time_ms();
	ret = born_philosophers(philo, &philo_info);
	if (ret != -1)
	{
		i = 0;
		while (i < philo_info.number)
		{
			sem_wait(philo_info.fin);
			i++;
		}
		kill_philosophers(&philo_info);
		free_resources(philo, &philo_info);
	}
	return (0);
}
