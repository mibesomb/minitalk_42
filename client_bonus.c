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

t_client	*confirmation;

int	ft_strlen(char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

void	send_null(int pid, int signum)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(pid, signum);
		usleep(90);
		i++;
	}
}

void	send_string(int pid, char *string)
{
	int	i;
	int	j;
	int	size;

	j = 0;
	size = ft_strlen(string);
	while (string[j] && j < size)
	{
		i = 7;
		while (i >= 0)
		{
			if (((string[j] >> i) & 1) == 1)
				kill(pid, SIGUSR1);
			else if (((string[j] >> i) & 1) == 0)
				kill(pid, SIGUSR2);
			usleep(500);
			i--;
		}
		j++;
	}
	send_null(pid, SIGUSR2);
}

void	handle_signal(int signum)
{
	if (signum == SIGUSR2)
	{
		confirmation->reception_signum = 1;
		return;
	}
}

int	main(int ac, char **av)
{
	int	pid_server;

	if (ac != 3)
		return (1);
	printf("Taille de la chaîne : %d\n", ft_strlen(av[2]));
	confirmation = malloc(sizeof(t_client));
	if (!confirmation)
		return (1);
	confirmation->reception_signum = 0;

	struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR2, &sa, NULL);

	pid_server = safe_atoi(av[1]);
	send_string(pid_server, av[2]);

	while (!confirmation->reception_signum)
		pause();

	free(confirmation);
	return (0);
}
