/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/11 22:48:19 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_philo_info(int argc, char **argv, t_philo_info *info)
{
	info->number = ft_atoui(argv[1]);
	info->time_to_die = ft_atoui(argv[2]);
	info->time_to_eat = ft_atoui(argv[3]);
	info->time_to_sleep = ft_atoui(argv[4]);
	if (info->number <= 0 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0)
		return (1);
	if (argc == 6)
	{
		info->must_eat_count = ft_atoui(argv[5]);
		if (info->must_eat_count == -1)
			return (1);
	}
	else
		info->must_eat_count = -1;
	info->fork = init_forks(info->number);
	if (!info->fork)
		return (2);
	if (pthread_mutex_init(&(info->key), NULL))
		return (2);
	info->dead_flag = 0;
	return (0);
}

int	born_philosophers(t_philo *philo, t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->number)
	{
		if (pthread_create(&(philo[i].thread), NULL, &philo_action, &philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	t_philo			*philo;
	int				ret;

	if ((argc != 5 && argc != 6))
		return (print_arg_error());
	ret = set_philo_info(argc, argv, &philo_info);
	if (ret == 1)
		return (print_arg_error());
	if (ret == 2)
		return (print_malloc_error());
	philo = malloc(sizeof(t_philo) * philo_info.number);
	if (!philo)
		return (print_malloc_error());
	init_philo(philo, &philo_info);
	philo_info.start_time = get_time_ms();
	pthread_mutex_lock(&philo_info.key);
	if (born_philosophers(philo, &philo_info))
		return (print_thread_error());
	pthread_mutex_unlock(&philo_info.key);
	monitor_dead(philo, &philo_info);
	if (free_resources(philo, &philo_info))
		return (1);
	return (0);
}
