/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:16:59 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/02 00:42:29 by jiskim           ###   ########.fr       */
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
	int 			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count; /* not essential */
	int				start_time;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
}			t_philo_info;

typedef struct s_philo
{
	int				index;
	int				last_eat_time;
	int				eat_count;
	t_philo_info	*info;
}			t_philo;

/* print_error */
int	print_arg_error(void);
int	print_malloc_error(void);

/* utils */
int	ft_strlen(char *str);
long	get_time_ms(void);

# endif
