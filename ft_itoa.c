/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibesomb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:20:11 by mibesomb          #+#    #+#             */
/*   Updated: 2025/06/16 20:20:17 by mibesomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*ft_strdup(const char *s)
{
	char	*copy;
	int		n;
	int		m;

	m = ft_strlen((char *)s);
	copy = (char *)malloc((m + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	n = 0;
	while (s[n])
	{
		copy[n] = s[n];
		n++;
	}
	copy[n] = '\0';
	return (copy);
}

static int	length_n(int n)
{
	int	taille;

	taille = 0;
	if (n <= 0)
		taille++;
	while (n)
	{
		n = n / 10;
		taille++;
	}
	return (taille);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		nb;
	int		x;

	nb = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		nb = -nb;
	x = length_n(n);
	ptr = (char *)malloc((x + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ptr[x] = '\0';
	x--;
	while (nb != 0 || x == length_n(nb) - 1)
	{
		ptr[x] = (nb % 10) + 48;
		nb = nb / 10;
		x--;
	}
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}
