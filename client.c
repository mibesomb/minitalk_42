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

static volatile sig_atomic_t	g_confirmation = 0;

void	wait_for_confirmation(void)
{
	while (!g_confirmation)
		pause();
	g_confirmation = 0;
}

void	send_bit(int pid, int bit)
{
	if (bit == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
	wait_for_confirmation();
	usleep(50);
}

void	handle_sig(int signum)
{
	if (signum == SIGUSR2)
		g_confirmation = 1;
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;
	int					size;

	if (ac != 3)
		return (1);
	pid = ft_atoi(av[1]);
	if (pid <= 0 || pid > 4194304)
		return (1);
	sa.sa_handler = handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	size = ft_strlen(av[2]);
	send_size(pid, size);
	send_string(pid, av[2]);
	return (0);
}
