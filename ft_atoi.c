/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibesomb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:22:55 by mibesomb          #+#    #+#             */
/*   Updated: 2025/06/16 20:22:56 by mibesomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *string)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (string[i] == 32 || string[i] == '\n' || string[i] == '\t'
		|| string[i] == '\v' || string[i] == '\r' || string[i] == '\f')
		i++;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			sign = -1;
		i++;
	}
	while (string[i] && (string[i] >= '0' && string[i] <= '9'))
	{
		result = (result * 10) + (string[i] - 48);
		i++;
	}
	return (result * sign);
}
