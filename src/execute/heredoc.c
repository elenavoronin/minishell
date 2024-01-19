/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 12:38:52 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/19 14:29:40 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(t_cmd *cmd)
{
	int		tmp;
	char	*input;

	tmp = open("temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp == -1)
		return (-1);
	input = readline("> ");
	while (input && ft_strcmp(input, cmd->delimiter))
	{
		// add_history(input);
		if (write(tmp, input, ft_strlen(input)) == -1
			|| write(tmp, "\n", 1) == -1)
		{
			perror("Error writing to temporary file");
			free(input);
			close(tmp);
			return (-1);
		}
		//expand variables
		free(input);
		input = readline("> ");
	}
	free(input);
	return (tmp);
}
