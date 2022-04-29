/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:25:54 by jiskim            #+#    #+#             */
/*   Updated: 2022/04/30 00:47:13 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_arg_error(void)
{
	write(STDERR_FILENO, "Invalid Argument.\n", 19);
	return (1);
}

int	print_malloc_error(void)
{
	write(STDERR_FILENO, "Memory Allocation Error.\n", 26);
	return (-1);
}
