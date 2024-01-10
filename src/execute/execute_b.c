/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:55:28 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/10 13:06:30 by dliu          ########   odam.nl         */
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
			free(new_paths);
			return (NULL);
		}
		pipes->path[nr] = ft_strjoin(path, cmd[0]);
		if (!pipes->path[nr])
		{
			free(new_paths);
			return (NULL);
		}
		if (access(pipes->path[nr], X_OK) == 0)
			return (pipes->path[nr]);
		free(path);
		j++;
	}
	return (NULL);
}

int	get_path(t_list **list, t_pipes *pipes, t_shell *state)
{
	int				i;
	t_cmd			*cmd;
	t_list			*cmds;

	i = 0;
	cmds = (*list);
	if (pipes->nr_pipes == 0)
	{
		cmd = cmds->content;
		if (check_builtins(&cmd->cmd_table[i]) == 1)
			pipes->path[i] = NULL;
		else
		{
			if (get_path_char(cmd->cmd_table, state->env.envp, pipes, i) == NULL)
				return (update_status(state, INTERNAL_ERROR), -1);
			return (0);
		}
	}
	i = 0;
	while (cmds)
	{
		cmd = cmds->content;
		if (check_builtins(&cmd->cmd_table[i]) == 1)
			pipes->path[i] = NULL;
		else
		{
			if (!get_path_char(cmd->cmd_table, state->env.envp, pipes, i))
				return (update_status(state, PIPE_ERROR), -1);
		}
		cmds = cmds->next;
		i++;
	}
	return (0);
}

int	redirect_input(t_list **list, t_pipes *pipes)
{
	int		i;
	t_cmd	*cmd;
	t_list	*all_cmd;
	int		fd;

	i = 0;
	all_cmd = (*list);
	while (all_cmd)
	{
		cmd = all_cmd->content;
		if (cmd->infile != NULL)
		{
			fd = open(cmd->infile, O_RDONLY, 0644);
			if (fd == -1)
				return (perror(cmd->infile), -1);
			pipes->fd_arr[i][0] = fd;
			if (dup2(pipes->fd_arr[i][0], STDIN_FILENO) == -1)
				return (perror("dup2"), -1);
		}
		all_cmd = all_cmd->next;
		i++;
	}
	return (0);
}

int	redirect_output(t_list **list, t_pipes *pipes)
{
	int		i;
	t_cmd	*cmd;
	t_list	*all_cmd;
	int		fd;

	i = 0;
	all_cmd = (*list);
	while (all_cmd)
	{
		cmd = all_cmd->content;
		if (cmd->outfile != NULL)
		{
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
				return (perror(cmd->outfile), -1);
			pipes->fd_arr[i][1] = fd;
			if (dup2(pipes->fd_arr[i][1], STDOUT_FILENO) == -1)
				return (perror("dup2"), -1);
		}
		all_cmd = all_cmd->next;
		i++;
	}
	return (0);
}

int	create_pipes(t_list **list, t_pipes *pipes, t_shell *state, int nr)
{
	t_list	*cmds;

	cmds = (*list);
	pipes->pid = malloc(sizeof(int) * (nr + 1));
	if (!pipes->pid)
		return (update_status(state, MALLOC_ERROR), -1);
	pipes->fd_arr = malloc(sizeof(t_pipe_fd) * (nr + 1));
	if (!pipes->fd_arr)
		return (update_status(state, MALLOC_ERROR), -1);
	pipes->path = malloc(sizeof(char *) * (nr + 1));
	if (!pipes->path)
		return (update_status(state, MALLOC_ERROR), -1);
	while (cmds)
	{
		pipes->return_value = 0;
		if (nr == 0)
		{
			pipes->nr_pipes = 0;
			return (0);
		}
		while (pipes->nr_pipes < nr)
		{
			if (pipe(pipes->fd_arr[pipes->nr_pipes + 1]) != 0)
				return (clear_pipes(pipes, pipes->nr_pipes), -1);
			pipes->nr_pipes++;
		}
		cmds = cmds->next;
	}
	return (0);
}
