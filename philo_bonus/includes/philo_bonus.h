/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:16:59 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/13 21:57:29 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define TWO_FORK_DEAD 2
# define ONE_FORK_DEAD 1
# define SUCCESS 0

# define ARG_ERROR 1
# define MALLOC_ERROR 2
# define THREAD_ERROR 3
# define DESTROY_ERROR 4

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct s_philo_info
{
	int				number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				dead_flag;
	int				full_philo;
	time_t			start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	key;
}			t_philo_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	time_t			last_eat_time;
	int				eat_count;
	int				already_full;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_philo_info	*info;
}			t_philo;

/* print_error */
int				print_error(int error_code);
/* initialize */
void			init_philo(t_philo *philo, t_philo_info *info);
pthread_mutex_t	*init_forks(int number);
int				init_data(int argc, char **argv, t_philo **philo,
					t_philo_info *info);

/* philo_action */
void			*philo_action(void *p);

/* philo_routine */
int				take_fork(t_philo *p, pthread_mutex_t *fork);
int				philo_eat(t_philo *p);
int				philo_sleep(t_philo *p);
int				philo_think(t_philo *p);

/* utils */
int				ft_strlen(char *str);
int				ft_atoui(char *argv);
time_t			get_time_ms(void);
time_t			get_passed_time(time_t start_time);

/* monitor_dead */
void			monitor_dead(t_philo *philo, t_philo_info *info);

int				free_fork(t_philo_info *info);
int				free_resources(t_philo *philo, t_philo_info *info, int num);

#endif
