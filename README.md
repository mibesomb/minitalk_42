# minitalk_42
# server : 
//while du main : condition pour sortir du while (bit = SIGUSR2 ?)
//globale to sig_atomic_t ?

//pas de struct globale : static, volatile sig_atomic_t
//ft_printf : write ft_strlen (gestion temps)
//ou juste write(1, &message, ft_strlen)
//minimum de demande dans handler
//tout dans le while() du main
//renvoyer signal a chaque bit a client pour l'autoriser a passer a la suite

//regle makefile pour bonus
//fichier avec mandatory + bonus


/*nt	ft_strlen(char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

void	chunck_init(char c)
{
	if (server->chunck_size == 0)
	{
		server->chunck = malloc(50 + 1 * sizeof(char));
		if (!server->chunck)
			return ;
		server->chunck_size = 50;
	}
	if (server->chunck_index >= server->chunck_size)
		return ;
	server->chunck[server->chunck_index] = c;
	server->chunck_index++;
}

void	print_message(char *message)
{
	server->chunck[server->chunck_index] = '\0';
	printf("message : %s\n", message);
	server->chunck_index = 0;
	free(server->chunck);
	free(server);
}

void	stock_character(int *bit_character)
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
	if (c == '\0')
	{
		print_message(server->chunck);
		return ;
	}
	else if (server->chunck_index < server->chunck_size)
		chunck_init(c);
	else
	{
		server->chunck = ft_realloc(server->chunck, server->chunck_size,
				server->chunck_size + 50);
		server->chunck_size += 50;
		server->chunck[server->chunck_index++] = c;
	}
}