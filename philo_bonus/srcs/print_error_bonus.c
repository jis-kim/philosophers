/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:25:54 by jiskim            #+#    #+#             */
/*   Updated: 2022/05/18 18:49:50 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(int error_code)
{
	if (error_code == ARG_ERROR)
		write(STDERR_FILENO, "Invalid Argument.\n", 19);
	if (error_code == MALLOC_ERROR)
		write(STDERR_FILENO, "Memory Allocation Error.\n", 26);
	if (error_code == FORK_ERROR)
		write(STDERR_FILENO, "Fork Process Error.\n", 21);
	if (error_code == THREAD_ERROR)
		write(STDERR_FILENO, "Thread Create Error.\n", 22);
	if (error_code == SEM_OPEN_ERROR)
		write(STDERR_FILENO, "Semaphore Open Error.\n", 23);
	else
		write(STDERR_FILENO, "Undefined error\n", 17);
	return (1);
}
