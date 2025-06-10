/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibesomb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:57:46 by mibesomb          #+#    #+#             */
/*   Updated: 2025/06/10 12:57:49 by mibesomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_global
{
	int		bit_character[8];
	int		index;
}			t_global;

t_global	*data;

void send_sign_back()
{
    int pid_client;

    pid_client = getpid();
    kill(pid_client, SIGUSR1);
}

void	print_character(int *bit_character)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	data->index = 0;
	while (i < 8)
	{
		if (bit_character[i] == 1)
			c |= (1 << (7 - i));
		i++;
	}
    if (c == '\0')
    {
		send_sign_back();
	}
	write(1, &c, 1);
}

void	stocking_bit(int signum)
{
	if (signum == SIGUSR1)
		data->bit_character[data->index] = 1;
	else if (signum == SIGUSR2)
		data->bit_character[data->index] = 0;
	data->index++;
	if (data->index == 8)
		print_character(data->bit_character);
}

int	main(void)
{
	void *ptr;

    ptr = &stocking_bit;
	data = malloc(sizeof(t_global));
	if (!data)
		return (1);
	data->index = 0;
	int pid_server = getpid();
	printf("pid server = %d\n", pid_server);
	signal(SIGUSR1, ptr);
	signal(SIGUSR2, ptr);
	while (1)
		pause();
}
