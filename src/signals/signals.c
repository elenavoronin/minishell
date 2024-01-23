/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/02 12:34:34 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/23 12:41:30 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(struct sigaction *sa)
{
	ft_bzero(sa, sizeof(sa));
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
	sa->sa_handler = &signal_handler;
	sigaction(SIGINT, sa, NULL);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = INTERRUPT;
		write(STDOUT_FILENO, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}
