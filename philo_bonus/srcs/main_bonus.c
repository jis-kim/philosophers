/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/15 22:35:23 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// -1이 success임..
int	born_philosophers(t_philo *philo, t_philo_info *info)
{
	int		i;
	pid_t	pid;

	i = 0;
	sem_wait(info->key);
	while (i < info->number)
	{
		pid = fork();
		if (pid == -1) // 부모 - 실패 (wait 후 에러)
		{
			info->dead_flag = 1;
			sem_post(info->key); //fail
			return (i);
		}
		if (pid == 0) // 자식 - while 그만둬야함
		{
			philo_action(&philo[i]);
			sem_post(info->key);
			return (-1);
		}
		// 부모 - 다음 create 진행 후 monitoring - 없어도 되는 조건..
		philo[i].pid = pid;
		i++;
	}
	sem_post(info->key);
	return (i);
}

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	t_philo			*philo;
	int				ret;

	if ((argc != 5 && argc != 6))
		return (print_error(ARG_ERROR));
	philo = NULL;
	ret = init_data(argc, argv, &philo, &philo_info);
	if (ret)
		return (print_error(ret));
	init_philo(philo, &philo_info);
	philo_info.start_time = get_time_ms();
	ret = born_philosophers(philo, &philo_info);
	if (ret >= 0)
	{
		free_resources(philo, &philo_info, ret);
		return (print_error(FORK_ERROR));
	}
	if (ret >= 0)
	{
		if (!free_resources(philo, &philo_info, ret))
			return (print_error(THREAD_ERROR));
		return (print_error(DESTROY_ERROR));
	}
	monitor_dead(philo, &philo_info);
	if (free_resources(philo, &philo_info, philo_info.number))
		return (print_error(DESTROY_ERROR));
	return (0);
}
