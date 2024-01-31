/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 12:38:52 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/31 19:26:45 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(char *delimiter)
{
	int		tmp;
	char	*input;

	tmp = open("/tmp/temp_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp == -1)
		return ;
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
		input = readline("> ");
	}
	free(input);
	close(tmp);
}

// int	read_heredoc(t_cmd *cmd)
// {
// 	int		tmp;
// 	char	*input;

// 	tmp = open("temp_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (tmp == -1)
// 		return (-1);
// 	input = readline("> ");
// 	while (input && ft_strcmp(input, cmd->delimiter))
// 	{
// 		if (write(tmp, input, ft_strlen(input)) == -1
// 			|| write(tmp, "\n", 1) == -1)
// 		{
// 			perror("🐢shell");
// 			free(input);
// 			close(tmp);
// 			return (-1);
// 		}
// 		free(input);
// 		input = readline("> ");
// 	}
// 	free(input);
// 	close(tmp);
// 	tmp = open("temp_heredoc", O_RDONLY, 0644);
// 	if (tmp == -1)
// 		return (-1);
// 	return (tmp);
// }
