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

#ifndef MINITALK_H
# define MINITALK_H

/*   LIBRARIES   */
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*   FUNCTIONS   */

// SERVER
void	handle_signal(int signum, siginfo_t *info, void *ucontext);
void	signal_back(pid_t pid);
void	process_bit(void);
int		bit_to_int(int *bit_array, int round);
void	bit_to_char(int *char_bits, int size);
void	print_message(char *msg, int size);

// CLIENT
void	handle_sig(int signum);
void	send_bit(int pid, int bit);
void	send_size(int pid, int size);
void	send_string(int pid, char *msg);
void	send_null(int pid);
void	wait_for_confirmation(void);

/*FUNCTIONS : utils*/
int		ft_strlen(char *string);
int		ft_atoi(char *string);
char	*ft_itoa(int n);

#endif
