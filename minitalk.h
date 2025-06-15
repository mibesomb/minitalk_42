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
# include <unistd.h>
# include <string.h>

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

/*   FUNCTIONS   */

// SERVER
void		print_character(int *bit_character);
void		signal_handling(int signum, siginfo_t *info, void *ucontext);
void		chunck_init(char c);

// CLIENT
int			ft_strlen(char *string);
void		send_string(int pid, char *string);

/*   FUNCTIONS : BONUS  */

// SERVER
void		send_sign(void);
int			multiple_clients(siginfo_t *info);

// CLIENT
void		send_null(int pid);
void		handle_signal(int signum);

/*FUNCTIONS : utils*/
int			ft_atoi(char *string);

#endif
