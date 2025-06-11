#include "minitalk.h"

int ft_atoi(char *string)
{
	int		i;
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
int ft_nb_digits(int nb)
{
    int count;

    count = 0;
    while (nb)
    {
        nb = nb / 10;
        count++;
    }
    return (count);
}

int safe_atoi(char *string)
{
    int nb;
    int nb_digits;

    nb = ft_atoi(string);
    nb_digits = ft_nb_digits(nb);
    if (nb_digits != 7)
        return (1);
    return (nb);
}