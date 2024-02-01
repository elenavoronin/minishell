/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 12:38:52 by evoronin      #+#    #+#                 */
/*   Updated: 2024/02/01 17:39:48 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(char *delimiter)
{
	int		tmp;
	char	*input;

	tmp = open("temp_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp == -1)
		return ;
	g_sig = READLINE;
	input = readline("> ");
	while (input && ft_strcmp(input, delimiter))
	{
		if (write(tmp, input, ft_strlen(input)) == -1
			|| write(tmp, "\n", 1) == -1)
		{
			perror("🐢shell");
			free(input);
			close(tmp);
			return ;
		}
		free(input);
		g_sig = READLINE;
		input = readline("> ");
		g_sig = SUCCESS;
	}
	free(input);
	close(tmp);
}
