/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2024/03/21 13:55:23 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_toolbox *tools)
{
	if (tools->cmd->heredoc)
		resolve_heredocs(tools->cmd, tools->env);
	if (ft_lstsize_m(tools->cmd) > 1)
		ft_executor_loop(tools->cmd, tools);
	else
	{
		if (ft_is_builtin(tools->cmd) == 0)
			ft_is_builtin_2(tools, tools->cmd);
		else if (ft_is_builtin(tools->cmd) != 0 && tools->cmd->cmd)
			simple_command(tools, tools->cmd);
	}
}

void	simple_command(t_toolbox *tools, t_command *cmd)
{
	int	status;

	cmd->pid = fork();
	if (cmd->pid < 0)
		(perror("minishell:"), exit(1));
	else if (cmd->pid == 0)
	{
		child_signals();
		manage_dups(cmd, NULL, NULL);
		if (cmd->heredoc && !cmd->args && cmd->in_fd <= 2)
		{
			if (dup2(cmd->heredoc, 0) < 0)
				(perror("minishell"), exit(1));
			close(cmd->heredoc);
		}
		manage_params_child(tools, cmd);
	}
	else
	{
		father_workout();
		if (waitpid(cmd->pid, &status, 0) == -1)
			(perror("minishell:"), exit(1));
	}
}

int	ft_is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (0);
	else
		return (1);
}

void	ft_is_builtin_2(t_toolbox *tools, t_command *cmd)
{
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(tools->env);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(tools);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(tools);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(tools);
}
