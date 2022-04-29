/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:16:59 by jiskim            #+#    #+#             */
/*   Updated: 2022/04/30 01:07:13 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

typedef struct s_philo_info
{
	int	number;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
}			t_philo_info;

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* print_error */
int	print_arg_error(void);
int	print_malloc_error(void);

/* utils */
int	ft_strlen(char *str);

# endif
