/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 12:38:52 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/17 15:39:52 by evoronin      ########   odam.nl         */
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
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		add_history(input);
		if (ft_strcmp(input, cmd->delimiter) == 0)
		{
			free(input);
			break ;
		}
		if (write(tmp, input, ft_strlen(input)) == -1) 
		{
			perror("Error writing to temporary file");
			free(input);
			close(tmp);
			return (-1);
		}
		if (write(tmp, "\n", 1) == -1)
		{
			perror("Error writing newline to temporary file");
			free(input);
			close(tmp);
			return (-1);
		}
		//expand variables
		free(input);
	}
	close(tmp);
	return (tmp);
}
