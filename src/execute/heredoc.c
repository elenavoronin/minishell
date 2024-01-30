/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 12:38:52 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/30 20:05:11 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(t_cmd *cmd)
{
	int		tmp;
	char	*input;

	tmp = open("temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp == -1)
		return (-1);
	input = readline("> ");
	while (input && ft_strcmp(input, cmd->delimiter))
	{
		if (write(tmp, input, ft_strlen(input)) == -1
			|| write(tmp, "\n", 1) == -1)
		{
			perror("🐢shell");
			free(input);
			close(tmp);
			return (-1);
		}
		free(input);
		input = readline("> ");
	}
	free(input);
	close(tmp);
	tmp = open("temp", O_RDONLY, 0644);
	if (tmp == -1)
		return (-1);
	return (tmp);
}
