/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/02 12:34:34 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/16 12:54:00 by dliu          ########   odam.nl         */
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
