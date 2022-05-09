/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/10 01:09:20 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_philo_info(int argc, char **argv, t_philo_info *info)
{
	info->number = ft_atoui(argv[1]);
	if (info->number <= 0)
		return (1);
	info->time_to_die = ft_atoui(argv[2]);
	if (info->time_to_die == -1)
		return (1);
	info->time_to_eat = ft_atoui(argv[3]);
	if (info->time_to_eat == -1)
		return (1);
	info->time_to_sleep = ft_atoui(argv[4]);
	if (info->time_to_sleep == -1)
		return (1);
	if (argc == 6)
	{
		info->must_eat_count = ft_atoui(argv[5]);
		if (info->must_eat_count == -1)
			return (2);
	}
	else
		info->must_eat_count = -1;
	info->fork = init_forks(info->number);
	if (!info->fork)
		return (1);
	if (pthread_mutex_init(&(info->key), NULL))
		return (1);
	info->dead_flag = 0;
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
	pthread_t		*philo_thread;
	t_philo_info	philo_info;
	t_philo			*philo;
	int				i;

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
	if (pthread_mutex_init(&philo_info.key, NULL))
		return (1);
	i = 0;
	philo_info.start_time = get_time_ms();
	pthread_mutex_lock(&philo_info.key);
	while (i < philo_info.number)
	{
		init_philo(i + 1, &philo[i], &philo_info);
		if (pthread_create(&philo_thread[i], NULL, &philo_action, &philo[i]))
			break ;
		i++;
	}
	pthread_mutex_unlock(&philo_info.key);
	monitor_dead(philo, &philo_info);
	i = 0;
	while (i < philo_info.number)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo_info.number)
	{
		pthread_mutex_destroy(&(philo->info->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&philo_info.key);
	return (0);
}
