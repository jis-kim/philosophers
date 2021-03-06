/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:25:54 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/13 15:34:19 by jiskim           ###   ########.fr       */
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
	return (1);
}

int	print_thread_error(void)
{
	write(STDERR_FILENO, "Thread Function Error.\n", 24);
	return (1);
}

int	print_destroy_error(void)
{
	write(STDERR_FILENO, "Mutex Destroy Error.\n", 22);
	return (1);
}

int	print_error(int error_code)
{
	if (error_code == ARG_ERROR)
		return (print_arg_error());
	if (error_code == MALLOC_ERROR)
		return (print_malloc_error());
	if (error_code == THREAD_ERROR)
		return (print_thread_error());
	if (error_code == DESTROY_ERROR)
		return (print_destroy_error());
	write(STDERR_FILENO, "Undefined error\n", 17);
	return (1);
}
