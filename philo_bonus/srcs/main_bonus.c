/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/18 19:04:14 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_child(t_philo *p)
{
	if (pthread_create(&(p->thread), NULL, monitor_dead, p))
	{
		print_error(THREAD_ERROR);
		exit(1);
	}
	pthread_detach(p->thread);
	philo_action(p);
	exit(0);
}

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
			philo_child(&philo[i]);
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
	waitpid(-1, NULL, 0);
	kill_philosophers(philo, &philo_info);
	free_resources(philo, &philo_info);
	return (0);
}
