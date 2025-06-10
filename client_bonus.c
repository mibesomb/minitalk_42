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

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//variable globale, incremente au fur et a mesure des bits

int	ft_strlen(char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
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
			usleep(100);
			i--;
		}
		j++;
	}
    printf("string sent !\n");
}
void sign_reception(int pid_server)
{
    //signal encoye au client pour confirmer message recu
}

int	main(int ac, char **av)
{
    int	pid_server;

	pid_server = atoi(av[2]);
	send_string(pid_server, av[3]);
    while(1)
        pause();
    return (0);
}
