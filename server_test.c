#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	g_bit = 0;

void	send_ack(pid_t pid)
{
	kill(pid, SIGUSR2);
}

int	bit_to_int(const int *bits, int count)
{
	int res = 0;
	for (int i = 0; i < count; i++)
		res = (res << 1) | bits[i];
	return (res);
}

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	static int	phase = 0;
	static int	size_bits[32];
	static int	char_bits[8];
	static int	bit_i = 0;
	static int	msg_size = 0;
	static char	*msg = NULL;
	static int	msg_i = 0;

	(void)ucontext;
	g_bit = (sig == SIGUSR1) ? 1 : 0;

	if (!phase) // Receive size
	{
		size_bits[bit_i++] = g_bit;
		if (bit_i == 32)
		{
			msg_size = bit_to_int(size_bits, 32);
			msg = malloc(msg_size + 1);
			if (!msg)
				exit(1);
			phase = 1;
			bit_i = 0;
		}
	}
	else // Receive message characters
	{
		char_bits[bit_i++] = g_bit;
		if (bit_i == 8)
		{
			char c = bit_to_int(char_bits, 8);
			msg[msg_i++] = c;
			if (msg_i == msg_size)
			{
				write(1, msg, msg_i - 1);
				write(1, "\n", 1);
				free(msg);
				msg = NULL;
				msg_i = 0;
				phase = 0;
			}
			bit_i = 0;
		}
	}

	send_ack(info->si_pid);
}

int	main(void)
{
	struct sigaction sa = {0};
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	printf("%d\n", getpid());
	while (1)
		pause();
	return (0);
}
