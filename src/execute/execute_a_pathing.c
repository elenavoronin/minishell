/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a_pathing.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:55:28 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/30 20:34:10 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**setup_paths(t_shell *shell)
{
	char	*path;
	char	**new_paths;

	path = getenv_value(shell->env, "PATH");
	if (!path)
		return (NULL);
	new_paths = ft_split(path, ':');
	if (!new_paths)
		update_status(shell, MALLOC_ERROR);
	return (new_paths);
}

int	get_path_char(t_shell *shell, t_pipes *pipes, int nr, char *cmd)
{
	char	**new_paths;
	int		i;

	i = 0;
	pipes->path[nr] = NULL;
	new_paths = setup_paths(shell);
	while (new_paths && new_paths[i])
	{
		pipes->path[nr] = ft_joinstrs(3, new_paths[i], "/", cmd);
		if (!pipes->path[nr])
		{
			ft_free_strarr(new_paths);
			return (update_status(shell, MALLOC_ERROR));
		}
		if (access(pipes->path[nr], X_OK) == 0)
		{
			ft_free_strarr(new_paths);
			return (SUCCESS);
		}
		free(pipes->path[nr]);
		pipes->path[nr] = NULL;
		i++;
	}
	ft_free_strarr(new_paths);
	return (1);
}

void	get_path(t_shell *shell, t_pipes *pipes)
{
	int		i;
	t_cmd	*cmd;
	t_list	*list;

	i = 0;
	list = shell->cmdlist;
	while (list != NULL && shell->status == SUCCESS)
	{
		cmd = list->content;
		if (cmd->cmd_table == NULL || check_builtins(cmd->cmd_table) == 1)
			pipes->path[i] = NULL;
		else
		{
			if (get_path_char(shell, pipes, i, cmd->cmd_table[0]) != SUCCESS)
			{
				if (access(cmd->cmd_table[0], X_OK) == 0)
				{
					pipes->path[i] = ft_strdup(cmd->cmd_table[0]);
					if (!pipes->path[i])
						update_status(shell, MALLOC_ERROR);
				}
			}
		}
		list = list->next;
		i++;
	}
}
