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

void	stock_msg(unsigned char c, int size, int pid)
{
	static int	index = 0;
	static char	*msg = NULL;

	if (!msg)
		msg = malloc(size + 1 * sizeof(char));
	if (!msg)
		return ;
	msg[index++] = c;
	if (c == '\0')
	{
		print_message(msg, index - 1);
		free(msg);
		msg = NULL;
		index = 0;
		kill(pid, SIGUSR2);
	}
}

int	bit_to_char(int signum, int pid, int size)
{
	static int				bit = 0;
	static unsigned char	c = 0;

	c = (c << 1) | (signum == SIGUSR1);
	kill(pid, SIGUSR2);
	bit++;
	if (bit == 8)
	{
		stock_msg(c, size, pid);
		bit = 0;
		if (c == '\0')
			return (0);
		c = 0;
	}
	return (1);
}

void	handle_signal(int signum, siginfo_t *info, void *ucontext)
{
	static int		bit = 0;
	static uint32_t	size = 0;
	static int		phase = 0;

	(void)ucontext;
	if (!phase)
	{
		size = (size << 1) | (signum == SIGUSR1);
		bit++;
		kill(info->si_pid, SIGUSR2);
		if (bit == 32)
		{
			phase = 1;
			bit = 0;
		}
		return ;
	}
	if (!bit_to_char(signum, info->si_pid, size))
	{
		phase = 0;
		bit = 0;
		size = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int pid;
	char *pid_server;

	(void)av;
	if (ac != 1)
		return (1);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	pid_server = ft_itoa(pid);
	write(1, pid_server, ft_strlen(pid_server));
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
