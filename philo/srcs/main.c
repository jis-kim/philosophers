/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/04/30 01:14:45 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_thread(void *info)
{
	printf("hello, world!(%d)\n", ((t_philo_info *)info)->number);
	return (info);
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
	pthread_t *philosophers;
	t_philo_info philo_info;
	int i;

	if (argc != 5 && argc != 6)
		return (print_arg_error());
	if (set_philo_info(argc, argv, &philo_info))
		return (print_arg_error());
	philosophers = malloc(sizeof(pthread_t) * philo_info.number);
	if (!philosophers)
		return (print_malloc_error());
	i = 0;
	while (i < philo_info.number)
	{
		pthread_create(&philosophers[i], NULL, &philo_thread, &philo_info);
		i++;
	}
	return (0);
}
