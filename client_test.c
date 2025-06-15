#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static volatile sig_atomic_t g_ack = 0;

void	handle_ack(int sig)
{
	(void)sig;
	g_ack = 1;
}

void	wait_ack(void)
{
	while (!g_ack)
		pause();
	g_ack = 0;
}

int	ft_strlen(const char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void	send_bit(int pid, int bit)
{
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	wait_ack();
	// Optionnel si tu veux ralentir un peu :
	// usleep(30);
}

void	send_size(int pid, int size)
{
	for (int i = 31; i >= 0; i--)
		send_bit(pid, (size >> i) & 1);
}

void	send_char(int pid, char c)
{
	for (int i = 7; i >= 0; i--)
		send_bit(pid, (c >> i) & 1);
}

void	send_message(int pid, const char *msg)
{
	int len = ft_strlen(msg);
	send_size(pid, len);
	for (int i = 0; msg[i]; i++)
		send_char(pid, msg[i]);
	send_char(pid, '\0'); // Terminaison
}

int	main(int ac, char **av)
{
	if (ac != 3)
		return (1);
	int pid = atoi(av[1]);
	if (pid <= 0)
		return (1);

	struct sigaction sa = {0};
	sa.sa_handler = &handle_ack;
	sigaction(SIGUSR2, &sa, NULL);

	printf("Sending message...\n");
	send_message(pid, av[2]);
	printf("Done.\n");
	return (0);
}
