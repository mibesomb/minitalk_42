/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibesomb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:15:54 by mibesomb          #+#    #+#             */
/*   Updated: 2025/06/15 21:15:56 by mibesomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_back(pid_t pid)
{
	pid = (int)pid;
	kill(pid, SIGUSR2);
}

void	print_message(char *msg, int size)
{
	write(1, msg, size);
}
