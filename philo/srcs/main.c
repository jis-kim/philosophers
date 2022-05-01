/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/02 01:10:04 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * eating, sleeping, thinking
 */
void *philo_task(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	pthread_mutex_lock(&(p->info->print));
	printf("%d philosopher test %ld\n", p->index, get_time_ms());
	pthread_mutex_unlock(&(p->info->print));
	return (p);
}

int		check_argv(char *argv)
{
	unsigned long long	num;
	int					length;

	num = 0;
	length = ft_strlen(argv);
	if (length > 10)
		return (-1);
	while (*argv)
	{
		if (*argv < '0' || *argv > '9')
			return (-1);
		num = num * 10 + (*argv - '0');
		if (num > 2147483647)
			return (-1);
		argv++;
	}
	return (num);
}

int	set_philo_info(int argc, char **argv, t_philo_info *info)
{
	int	num;

	num = 0;
	num = check_argv(argv[1]);
	if (num <= 0)
		return (1);
	info->number = num;
	info->fork = malloc(sizeof(pthread_mutex_t) * num);
	if (!info->fork)
		return (1);
	num = check_argv(argv[2]);
	if (num == -1)
		return (1);
	info->time_to_die = num;
	num = check_argv(argv[3]);
	if (num == -1)
		return (1);
	info->time_to_eat = num;
	num = check_argv(argv[4]);
	if (num == -1)
		return (1);
	info->time_to_sleep = num;
	if (argc == 6)
	{
		num = check_argv(argv[5]);
		if (num == -1)
			return (1);
		info->must_eat_count = num;
	}
	else
		info->must_eat_count = -1;
	return (0);
}

/**
 * @brief
 *
 * @param argc 5 or 6
 * @param argv
 * 1. number_of_philosophers
 * 2. time_to_die
 * 3. time_to_eat
 * 4. time_to_sleep
 * 5. [number_of_time_each_philosopher_must_eat]
 * @return int
 */
int	main(int argc, char **argv)
{
	pthread_t *philo_thread;
	t_philo_info philo_info;
	t_philo	*philo;
	int i;

	if (argc != 5 && argc != 6)
		return (print_arg_error());
	if (set_philo_info(argc, argv, &philo_info))
		return (print_arg_error());
	philo_thread = malloc(sizeof(pthread_t) * philo_info.number);
	if (!philo_thread)
		return (print_malloc_error());
	philo = malloc(sizeof(t_philo) * philo_info.number);
	if (!philo)
		return (print_malloc_error());
	i = 0;
	while (i < philo_info.number)
	{
		philo[i].info = &philo_info;
		philo[i].index = i + 1;
		pthread_create(&philo_thread[i], NULL, &philo_task, &philo[i]);
		i++;
	}
	return (0);
}
