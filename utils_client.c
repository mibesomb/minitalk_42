/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibesomb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:20:25 by mibesomb          #+#    #+#             */
/*   Updated: 2025/06/16 20:20:27 by mibesomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_null(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		send_bit(pid, 0);
		i++;
	}
}

void	send_string(int pid, char *msg)
{
	int	i;
	int	j;

	j = 0;
	while (msg[j])
	{
		i = 7;
		while (i >= 0)
		{
			send_bit(pid, (msg[j] >> i) & 1);
			i--;
		}
		j++;
	}
	send_null(pid);
}

void	send_size(int pid, int size)
{
	int	i;

	i = 31;
	while (i >= 0)
	{
		send_bit(pid, (size >> i) & 1);
		i--;
	}
}
