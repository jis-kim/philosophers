/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:15:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/07 00:41:50 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * eating, sleeping, thinking
 * 짝수면 n + 1, 홀수면 n번째 포크를 집는다?
 */
void *philo_task(void *philo)
{
	t_philo	*p;
	int		first;
	int		second;

	p = (t_philo *)philo;
	if (p->index % 2 == 1)
	{
		first = p->index - 2;
		second = p->index - 1;
	}
	else
	{
		first = p->index - 1;
		second = p->index - 2;
	}
	if (p->index == 1)
		first = p->info->number - 1;
	if (p->index == p->info->number)
		second = 0;

	while (1)
	{
		/* odd -> left (index - 1), even -> right */
		pthread_mutex_lock(&(p->info->fork[first]));
		if (p->info->dead_flag)
		{
			pthread_mutex_unlock(&(p->info->fork[first]));
			return (NULL);
		}
		pthread_mutex_lock(&(p->info->print));
		printf("%ld %d has taken a fork\n", get_passed_time(p->info->start_time), p->index);
		pthread_mutex_unlock(&(p->info->print));
		/* odd -> right, even -> left */
		pthread_mutex_lock(&(p->info->fork[second]));

		if (p->info->dead_flag)
		{
			pthread_mutex_unlock(&(p->info->fork[first]));
			pthread_mutex_unlock(&(p->info->fork[second]));
			return (NULL);
		}
		pthread_mutex_lock(&(p->info->print));
		printf("%ld %d has taken a fork\n", get_passed_time(p->info->start_time), p->index);
		pthread_mutex_unlock(&(p->info->print));

		if (p->info->dead_flag)
		{
			pthread_mutex_unlock(&(p->info->fork[first]));
			pthread_mutex_unlock(&(p->info->fork[second]));
			return (NULL);
		}
		pthread_mutex_lock(&(p->info->print));
		printf("%ld %d is eating\n", get_passed_time(p->info->start_time), p->index);
		pthread_mutex_unlock(&(p->info->print));

	// 생각을 해봐 지수야..
	// 먹는동안 sleep이야.. 근데? 지금 시간이 먹기 시작한 시간으로부터 eat_time전까지여야돼
		long now = get_passed_time(p->info->start_time);
		pthread_mutex_lock(&(p->info->print));
		p->last_eat_time = now;
		pthread_mutex_unlock(&(p->info->print));
		while (get_passed_time(p->info->start_time) < p->info->time_to_eat + now)
		{
			if (p->info->dead_flag)
			{
				pthread_mutex_unlock(&(p->info->fork[first]));
				pthread_mutex_unlock(&(p->info->fork[second]));
				return (NULL);
			}
			usleep(200);
		}
		p->eat_count++;

		pthread_mutex_unlock(&(p->info->fork[first]));
		pthread_mutex_unlock(&(p->info->fork[second]));

		if (p->info->dead_flag)
			return (NULL);
		pthread_mutex_lock(&(p->info->print));
		printf("%ld %d is sleeping\n", get_passed_time(p->info->start_time), p->index);
		pthread_mutex_unlock(&(p->info->print));
		now = get_passed_time(p->info->start_time);
		while (get_passed_time(p->info->start_time) < p->info->time_to_sleep  + now)
		{
			if (p->info->dead_flag)
				return (NULL);
			usleep(200);
		}
		if (p->info->dead_flag)
			return (NULL);
		pthread_mutex_lock(&(p->info->print));
		printf("%ld %d is thinking\n", get_passed_time(p->info->start_time), p->index);
		pthread_mutex_unlock(&(p->info->print));
		if (p->info->dead_flag)
			return (NULL);
	}
	return (NULL);
}

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
	if (pthread_mutex_init(&(info->print), NULL))
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
	pthread_t *philo_thread;
	t_philo_info philo_info;
	t_philo	*philo;
	int i;
	time_t	now;

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
	if (pthread_mutex_init(&philo_info.print, NULL))
		return (1);
	i = 0;
	philo_info.start_time = get_time_ms();
	while (i < philo_info.number)
	{
		init_philosophers(i + 1, &philo[i], &philo_info);
		if (pthread_create(&philo_thread[i], NULL, &philo_task, &philo[i]))
			break;
		i++;
	}
	i = 0;
	while (1)
	{
		if (i == philo_info.number)
			i = 0;
		now = get_passed_time(philo->info->start_time);
		if (check_dead(&philo[i], now))
		{
			pthread_mutex_lock(&philo_info.print);
			printf("%ld %d \033[31mis died\n\033[0m", now, philo_info.dead_flag);
			pthread_mutex_unlock(&philo_info.print);
			break;
		}
		i++;
		usleep(200);
	}
	i = 0;
	while (i < philo_info.number)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}
	while (i < philo_info.number)
	{
		pthread_mutex_destroy(&(philo->info->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&philo_info.print);
	return (0);
}
