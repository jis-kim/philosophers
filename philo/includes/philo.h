/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:16:59 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/07 00:42:21 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_info
{
	int				number;
	long 			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count; /* not essential */
	time_t			start_time;
	int				dead_flag;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
}			t_philo_info;

typedef struct s_philo
{
	int				index;
	time_t			last_eat_time;
	int				eat_count;
	t_philo_info	*info;
}			t_philo;

/* print_error */
int	print_arg_error(void);
int	print_malloc_error(void);

/* initialize */
void	init_philosophers(int index, t_philo *philo, t_philo_info *info);
pthread_mutex_t	*init_forks(int number);

/* utils */
int	ft_strlen(char *str);
int	ft_atoui(char *argv);
time_t	get_time_ms(void);
time_t	get_passed_time(time_t start_time);

/* check_dead */
int	check_dead(t_philo *philo, time_t now);

# endif
