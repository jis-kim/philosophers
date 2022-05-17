/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:39:05 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/16 21:19:02 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int set_philo_info(int argc, char **argv, t_philo_info *info)
{
	info->number = ft_atoui(argv[1]);
	info->time_to_die = ft_atoui(argv[2]);
	info->time_to_eat = ft_atoui(argv[3]);
	info->time_to_sleep = ft_atoui(argv[4]);
	if (info->number <= 0 || info->time_to_die < 0 || info->time_to_eat < 0
			|| info->time_to_sleep < 0)
		return (ARG_ERROR);
	info->must_eat_count = -1;
	if (argc == 6)
	{
		info->must_eat_count = ft_atoui(argv[5]);
		if (info->must_eat_count == -1)
			return (ARG_ERROR);
	}
	info->fork = init_forks(info->number);
	if (!info->fork)
		return (MALLOC_ERROR);
	sem_unlink(KEY);
	info->key = sem_open(KEY, O_CREAT, 0644, 1);
	if (info->key == SEM_FAILED)
	{
		free_fork(info);
		return (MALLOC_ERROR);
	}
	return (0);
}

void init_philo(t_philo *philo, t_philo_info *info)
{
	int i;

	i = 0;
	while (i < info->number)
	{
		philo[i].index = i + 1;
		philo[i].info = info;
		philo[i].last_eat_time = info->start_time;
		philo[i].eat_count = 0;
		i++;
	}
}
#include <string.h>
#include <errno.h>

sem_t *init_forks(int number)
{
	int i;
	sem_t *fork;

	i = 0;
	sem_unlink(FORK); // if fork is already opened
	fork = sem_open(FORK, O_CREAT, 0644, number);
	printf("%s\n", strerror(errno));
	if (fork == SEM_FAILED)
		return (NULL);
	return (fork);
}

int init_data(int argc, char **argv, t_philo **philo, t_philo_info *info)
{
	int ret;

	ret = set_philo_info(argc, argv, info);
	if (ret)
		return (ret);
	*philo = malloc(sizeof(t_philo) * info->number);
	if (!(*philo))
	{
		if (free_resources(*philo, info))
			return (DESTROY_ERROR);
		return (MALLOC_ERROR);
	}
	return (0);
}