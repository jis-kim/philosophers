/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/17 21:39:54 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	born_philosophers(t_philo *philo, t_philo_info *info)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < info->number)
	{
		pid = fork();
		if (pid == -1)
		{
			while (i > 0)
				kill(philo[--i].pid, SIGTERM);
			exit(1);
		}
		if (pid == 0)
		{
			pthread_create(&philo[i].thread, NULL, monitor_dead, &philo[i]);
			pthread_detach(philo[i].thread);
			philo_action(&philo[i]);
			exit(0);
		}
		philo[i].pid = pid;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	t_philo			*philo;
	int				i;

	if ((argc != 5 && argc != 6))
		return (print_error(ARG_ERROR));
	philo = NULL;
	init_data(argc, argv, &philo, &philo_info);
	init_philo(philo, &philo_info);
	philo_info.start_time = get_time_ms();
	born_philosophers(philo, &philo_info);
	i = 0;
	while (i < philo_info.number)
	{
		sem_wait(philo_info.fin);
		i++;
	}
	kill_philosophers(philo, &philo_info);
	while (waitpid(-1, NULL, 0) != -1)
		;
	free_resources(philo, &philo_info);
	return (0);
}
