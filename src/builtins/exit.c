/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:30:16 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/31 14:00:15 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_status(t_shell *shell, char **cmd)
{
	int		i;
	int		j;

	if (!cmd || !cmd[1])
		return (SUCCESS);
	cmd++;
	i = 0;
	while (cmd[0][i])
	{
		if (!ft_isdigit(cmd[0][i]))
		{
			ft_perror("🐢shell", "exit", "a numeric argument required");
			shell->return_value = SYNTAX_ERROR;
			return (SUCCESS);
		}
	}
	cmd++;
	if (cmd)
	{
		ft_perror("🐢shell", "exit", "too many arguments");
		return (SYNTAX_ERROR);
	}
	shell->return_value = ft_atoi(cmd[0]);
	return (SUCCESS);
}

int	mini_exit(t_shell *shell, char **cmd, int fd)
{
	if (check_status(shell, cmd) != SUCCESS)
		return (SYNTAX_ERROR);
	ft_putendl_fd("exit", fd);
	free(shell->line);
	ft_lstclear(&shell->cmdlist, delete_cmd);
	clear_env(&shell->env);
	shell->run = 0;
	clear_history();
	exit(shell->return_value);
}
