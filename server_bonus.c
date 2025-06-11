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

t_server	*data;

void	clear_bit(void)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		data->bit_character[i] = 0;
		i++;
	}
}
void	send_sign(void)
{
	if (data->client_pid > 0)
		kill(data->client_pid, SIGUSR2);
}

void	print_character(int *bit_character)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (i < 8)
	{
		if (bit_character[i] == 1)
			c |= (1 << (7 - i));
		i++;
	}
	data->index = 0;
	clear_bit();
	usleep(90);
	if (c == '\0')
	{
		send_sign();
		data->end = 1;
		return ;
	}
	write(1, &c, 1);
}
int	multiple_clients(siginfo_t *info)
{
	pid_t	sender_pid;

	sender_pid = info->si_pid;
	if (data->client_pid && (info->si_pid != data->client_pid))
		return (1);
	if (data->client_pid == 0 || data->end)
	{
		data->client_pid = sender_pid;
		data->index = 0;
		clear_bit();
		data->end = 0;
		return (0);
	}
	if (sender_pid != data->client_pid)
		return (1);
	return (0);
}

void	signal_handling(int signum, siginfo_t *info, void *ucontext)
{
	int	check_client;

	(void)ucontext;
	check_client = multiple_clients(info);
	if (check_client || data->end)
		return ;
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
	struct sigaction	sa;
	int					pid_server;

	data = malloc(sizeof(t_server));
	if (!data)
		return (1);
	data->index = 0;
	data->end = 0;
	data->client_pid = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handling;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid_server = getpid();
	printf("%d\n", pid_server);
	while (1)
		pause();
}
