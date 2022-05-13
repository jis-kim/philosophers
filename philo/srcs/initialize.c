/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:39:05 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/13 15:36:19 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_philo_info(int argc, char **argv, t_philo_info *info)
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
	if (pthread_mutex_init(&(info->key), NULL))
	{
		if (!free_fork(info))
			return (THREAD_ERROR);
		return (DESTROY_ERROR);
	}
	info->dead_flag = 0;
	return (0);
}

void	init_philo(t_philo *philo, t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->number)
	{
		philo[i].index = i + 1;
		philo[i].info = info;
		philo[i].last_eat_time = info->start_time;
		philo[i].eat_count = 0;
		philo[i].already_full = 0;
		if (i == 0)
		{
			philo[i].left = &info->fork[0];
			philo[i].right = &info->fork[info->number - 1];
		}
		else
		{
			philo[i].left = &info->fork[i];
			philo[i].right = &info->fork[i - 1];
		}
		i++;
	}
}

pthread_mutex_t	*init_forks(int number)
{
	int				i;
	pthread_mutex_t	*fork;

	i = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number);
	if (!fork)
		return (NULL);
	while (i < number)
	{
		if (pthread_mutex_init(&fork[i], NULL))
		{
			while (i--)
				pthread_mutex_destroy(&fork[i]);
			free(fork);
			return (NULL);
		}
		i++;
	}
	return (fork);
}

int	init_data(int argc, char **argv, t_philo **philo, t_philo_info *info)
{
	int	ret;

	ret = set_philo_info(argc, argv, info);
	if (ret)
		return (ret);
	*philo = malloc(sizeof(t_philo) * info->number);
	if (!(*philo))
	{
		if (free_resources(*philo, info, info->number))
			return (DESTROY_ERROR);
		return (MALLOC_ERROR);
	}
	return (0);
}
