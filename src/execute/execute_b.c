/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:55:28 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/11 17:23:08 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_char(char **cmd, char **envp, t_pipes *pipes, int nr)
{
	char	**new_paths;
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_paths = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen("PATH")))
		{
			new_paths = ft_split(envp[i], ':');
			if (!new_paths)
				return (NULL);
			break ;
		}
		else
			i++;
	}
	while (new_paths[j] != NULL)
	{
		path = ft_strjoin(new_paths[j], "/");
		if (!path)
		{
			ft_free_strarr(new_paths);
			return (NULL);
		}
		pipes->path[nr] = ft_strjoin(path, cmd[0]);
		if (!pipes->path[nr])
		{
			ft_free_strarr(new_paths);
			free(path);
			return (NULL);
		}
		if (access(pipes->path[nr], X_OK) == 0)
		{
			ft_free_strarr(new_paths);
			free(path);
			return (pipes->path[nr]);
		}
		free(path);
		j++;
	}
	ft_free_strarr(new_paths);
	pipes->path[nr] = NULL;
	return (NULL);
}

void	get_path_b(t_list *list, t_pipes *pipes, t_shell *state)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	while (list)
	{
		cmd = list->content;
		if (check_builtins(&cmd->cmd_table[i]) == 1)
			pipes->path[i] = NULL;
		else
		{
			if (get_path_char(cmd->cmd_table, state->env.envp,
					pipes, i) == NULL)
				state->return_value = 127;
		}
		list = list->next;
		i++;
	}
}

void	get_path_a(t_list *list, t_pipes *pipes, t_shell *state)
{
	int				i;
	t_cmd			*cmd;

	i = 0;
	if (pipes->nr_pipes == 0)
	{
		cmd = list->content;
		if (check_builtins(&cmd->cmd_table[i]) == 1)
		{
			free(pipes->path);
			pipes->path = NULL;
		}
		else
		{
			if (get_path_char(cmd->cmd_table,
					state->env.envp, pipes, i) == NULL)
				state->return_value = 127;
		}
	}
	else
		get_path_b(list, pipes, state);
}

void	redirect_input(t_list *list, t_pipes *pipes, t_shell *shell)
{
	int		i;
	t_cmd	*cmd;
	int		fd;

	i = 0;
	while (list)
	{
		cmd = list->content;
		if (cmd->infile != NULL)
		{
			fd = open(cmd->infile, O_RDONLY, 0644);
			if (fd == -1)
			{
				shell->return_value = errno;
				return ;
			}
			pipes->fd_arr[i][0] = fd;
			if (dup2(pipes->fd_arr[i][0], STDIN_FILENO) == -1)
			{
				shell->return_value = errno;
				return ;
			}
		}
		list = list->next;
		i++;
	}
}

void	redirect_output(t_list *list, t_pipes *pipes, t_shell *shell)
{
	int		i;
	t_cmd	*cmd;
	int		fd;

	i = 0;
	while (list)
	{
		cmd = list->content;
		if (cmd->outfile != NULL)
		{
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				shell->return_value = errno;
				return ;
			}
			pipes->fd_arr[i][1] = fd;
			if (dup2(pipes->fd_arr[i][1], STDOUT_FILENO) == -1)
			{
				shell->return_value = errno;
				return ;
			}
		}
		list = list->next;
		i++;
	}
}
