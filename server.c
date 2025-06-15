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

static int	g_bit;

int	bit_to_int(int *bit_array, int round)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < round)
	{
		res |= (bit_array[i] << i);
		i++;
	}
	return (res);
}

void	bit_to_char(int *char_bits, int *size)
{
	static char	*msg = NULL;
	static int	char_index = 0;
	static char	c;

	if (!msg)
	{
		msg = malloc((*size + 1) * sizeof(char));
		if (!msg)
			return ;
	}
	c = bit_to_int(char_bits, 8);
	msg[char_index++] = c;
	if (c == '\0')
	{
		print_message(msg, char_index - 1);
		free(msg);
		msg = NULL;
		char_index = 0;
		c = 0;
	}
	size = 0;
}

void	process_bit(void)
{
	static int	phase = 0;
	static int	bit_i = 0;
	static int	size_bits[32];
	static int	char_bits[8];
	int	size;

	if (!phase)
	{
		size_bits[bit_i++] = g_bit;
		if (bit_i == 32)
		{
			bit_i = 0;
			size = bit_to_int(size_bits, 32);
			phase = 1;
		}
	}
	else
	{
		char_bits[bit_i++] = g_bit;
		if (bit_i == 8)
		{
			bit_i = 0;
			bit_to_char(char_bits, &size);
		}
	}
}

void	handle_signal(int signum, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (signum == SIGUSR1)
		g_bit = 1;
	else if (signum == SIGUSR2)
		g_bit = 0;
	signal_back(info->si_pid);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t					pid_server;
	char *pid_str;

	(void)av;
	if (ac != 1)
		return (1);
	g_bit = 0;
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid_server = getpid();
	pid_str = ft_itoa(pid_server);
	write(1, pid_str, ft_strlen(pid_str));
	write(1, "\n", 1);
	while (1)
	{
		pause();
		process_bit();
	}
	return (0);
}
