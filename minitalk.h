
#ifndef MINITALK_H
# define MINITALK_H

/*   LIBRARIES   */
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/*   STRUCTURES   */

typedef struct s_server
{
	int		bit_character[8];
	int		index;
    int     end;
	pid_t	client_pid;
}			t_server;

typedef struct s_client
{
	int		reception_signum;

}			t_client;

/*   FUNCTIONS   */

//SERVER
void	print_character(int *bit_character);
void	signal_handling(int signum, siginfo_t *info, void *ucontext);

//CLIENT
int	ft_strlen(char *string);
void	send_string(int pid, char *string);

/*   FUNCTIONS : BONUS  */

//SERVER
void	send_sign(void);
int     multiple_clients(siginfo_t *info);

//CLIENT
void	send_null(int pid, int signum);
void	handle_signal(int signum);

/*FUNCTIONS : utils*/
int safe_atoi(char *string);
int ft_nb_digits(int nb);
int ft_atoi(char *string);

#endif