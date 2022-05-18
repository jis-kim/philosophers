/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:16:59 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/18 18:50:04 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define TWO_FORK_DEAD 2
# define ONE_FORK_DEAD 1
# define SUCCESS 0

# define ARG_ERROR 1
# define MALLOC_ERROR 2
# define FORK_ERROR 3
# define THREAD_ERROR 4
# define SEM_OPEN_ERROR 5

# define FORK "fork"
# define KEY "key"
# define FIN "fin"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_info
{
	int				number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	sem_t			*fork;
	sem_t			*key;
	sem_t			*fin;
	time_t			start_time;
}			t_philo_info;

typedef struct s_philo
{
	pid_t			pid;
	int				index;
	int				eat_count;
	time_t			last_eat_time;
	pthread_t		thread;
	t_philo_info	*info;
}			t_philo;

/* print_error */
int		print_error(int error_code);

/* initialize */
void	init_philo(t_philo *philo, t_philo_info *info);
sem_t	*init_forks(int number);
void	init_data(int argc, char **argv, t_philo **philo, t_philo_info *info);

/* philo_action */
void	*philo_action(void *p);

/* philo_routine */
void	take_fork(t_philo *p);
void	philo_eat(t_philo *p);
void	philo_sleep(t_philo *p);
void	philo_think(t_philo *p);

/* utils */
int		ft_strlen(char *str);
int		ft_atoui(char *argv);
time_t	get_time_ms(void);
time_t	get_passed_time(time_t start_time);
int		kill_philosophers(t_philo *philo, t_philo_info *info);

/* monitor_dead */
void	*monitor_dead(void *p);

/* destroy */
void	expire_sem(sem_t *sem, const char *sem_name);
void	free_resources(t_philo *philo, t_philo_info *info);

#endif
