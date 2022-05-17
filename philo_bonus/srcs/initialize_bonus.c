/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:39:05 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/17 20:36:47 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t *init_forks(int number)
{
	int i;
	sem_t *fork;

	i = 0;
	sem_unlink(FORK);
	fork = sem_open(FORK, O_CREAT | O_EXCL, 0644, number);
	if (fork == SEM_FAILED)
	{
		print_error(SEM_OPEN_ERROR);
		exit(1);
	}
	return (fork);
}

void set_info(int argc, char **argv, t_philo_info *info)
{
	info->number = ft_atoui(argv[1]);
	info->time_to_die = ft_atoui(argv[2]);
	info->time_to_eat = ft_atoui(argv[3]);
	info->time_to_sleep = ft_atoui(argv[4]);
	if (info->number <= 0 || info->time_to_die < 0 || info->time_to_eat < 0
			|| info->time_to_sleep < 0)
	{
		print_error(ARG_ERROR);
		exit(1);
	}
	info->must_eat_count = -1;
	if (argc == 6)
	{
		info->must_eat_count = ft_atoui(argv[5]);
		if (info->must_eat_count == -1)
		{
			print_error(ARG_ERROR);
			exit(1);
		}
	}
}

static void set_sem(t_philo_info *info)
{
	info->fork = init_forks(info->number);
	sem_unlink(KEY);
	info->key = sem_open(KEY, O_CREAT, 0644, 1);
	if (info->key == SEM_FAILED)
	{
		expire_sem(info->fork, FORK);
		print_error(SEM_OPEN_ERROR);
		exit(1);
	}
	sem_unlink(FIN);
	info->fin = sem_open(FIN, O_CREAT, 0644, 0);
	if (info->fin == SEM_FAILED)
	{
		expire_sem(info->key, KEY);
		expire_sem(info->fork, FORK);
		print_error(SEM_OPEN_ERROR);
		exit(1);
	}
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

void init_data(int argc, char **argv, t_philo **philo, t_philo_info *info)
{
	set_info(argc, argv, info);
	set_sem(info);
	*philo = malloc(sizeof(t_philo) * info->number);
	if (!(*philo))
	{
		free_resources(*philo, info);
		print_error(MALLOC_ERROR);
		exit(1);
	}
}
