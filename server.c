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

#include "minitalk.h"

static int g_bit;

int bit_to_int(int *bit_array)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (i < 32)
	{
		res <<= 1;
		res |= bit_array[i];
		i++;
	}
	return (res);
}

int size_init()
{
	static int bits[32];
	static int index;
	int size;

	index = 0;
	if (index < 32)
	{
		bits[index] = g_bit;
		index++;
		return (0);
	}
	else
	{
		size = bit_to_int(&bits);
		index = 0;
	}
	return (size);
}
void print_message(char *msg, int size)
{
	msg[size] = '\0';
	write(1, msg, size);
}

void bit_to_char(int size)
{
	static char 	*msg = NULL;
	static int		i = 0;
	static int 		j = 0;
	static char		c = 0;

	if (!msg)
	{
		msg = malloc(size + 1 * sizeof(char));
		if (!msg)
			return ;
	}
	c |= (g_bit << (7 - i++));
	if (i == 8)
	{
		msg[j++] = c;
		if (c == '\0')
		{
			print_message(msg, size);
			free(msg);
			msg = NULL;
			j = 0;
		}
		c = '0';
		i = 0;
	}
}

void process_bit(void)
{
	static int phase = 0;
	int size;

	if (!phase)
	{
		size = size_init();
		if (size)
			phase = 1;
		else
			return ;
	}
	else if (pause)
	{
		if (bit_to_char(size))
			phase = 0;
	}
}
void signal_back(pid_t pid)
{
	pid = (int)pid;
	kill(pid, SIGUSR2);

}
void	handle_signal(int signum, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (signum == SIGUSR1)
		g_bit = 1;
	else if (signum == SIGUSR2)
		g_bit = 0;
	signal_back(info->sig_pid);
}

int	main(int ac, char **av)
{
	struct sigaction sa;
	(void)av;
	if (ac != 1)
		return (1);
	g_bit = 0;
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("%d\n", getpid());
	while (1)
	{
		pause();
		process_bit();
	}
	return (0);
}
