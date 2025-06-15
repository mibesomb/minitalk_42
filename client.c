/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibesomb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:57:38 by mibesomb          #+#    #+#             */
/*   Updated: 2025/06/10 12:57:40 by mibesomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static volatile sig_atomic_t g_confirmation = 0;

int	ft_strlen(char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

void	send_null(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		usleep(90);
		i++;
	}
}

void handle_signal(int signum)
{
	(void)signum;
	g_confirmation = 1;
    const char *msg = "Signal reçu\n";
    write(1, msg, 12);

}

void wait_for_confirmation(void)
{
	while (!g_confirmation)
		pause();
	g_confirmation = 0;
}

void send_bit(int pid, int bit)
{
	if (bit == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	wait_for_confirmation();
}

void send_string(int pid, char *msg)
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

void send_size(int pid, int size)
{
	int i;

	i = 31;
	while (i >= 0)
	{
		send_bit(pid, (size >> i) & 1);
		i--;
	}
}

int main(int ac, char **av)
{
	int pid;
	struct sigaction sa;
	int size;

	if (ac != 3)
		return (1);
	pid = ft_atoi(av[1]);
	if (pid <= 0 || pid > 4194304)
		return (1);

	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	size = ft_strlen(av[2]);
	printf("siz of msg = %d\n", size);
	if (!size)
		return (1);
	send_size(pid, size);
	send_string(pid, av[2]);
	return (0);
}
