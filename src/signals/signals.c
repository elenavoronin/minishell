/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/02 12:34:34 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/30 16:03:00 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_after_rl(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = INTERRUPT;
	}
}

void	signal_handler_before_rl(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = INTERRUPT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals_after_rl(struct sigaction *sa)
{
	g_sig = SUCCESS;
	ft_bzero(sa, sizeof(sa));
	sa->sa_handler = &signal_handler_after_rl;
	sigaction(SIGQUIT, sa, NULL);
	sa->sa_handler = &signal_handler_after_rl;
	sigaction(SIGINT, sa, NULL);
}

void	init_signals_before_rl(struct sigaction *sa)
{
	ft_bzero(sa, sizeof(sa));
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
	sa->sa_handler = &signal_handler_before_rl;
	sigaction(SIGINT, sa, NULL);
}
