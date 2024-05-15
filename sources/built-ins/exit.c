/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:44:34 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/15 17:45:45 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	exit_num_err(t_toolbox *tools)
{
	ft_putstr_fd("bash: exit: a: se requiere un argumento numérico\n", 2);
	g_exit_status = 1;
	free(tools->old_pwd);
	free(tools->home_dir);
	free(tools->pwd);
	free_arr(tools->env);
	tools_reload(tools);
	free(tools);
	return (exit_code());
}

int	exit_clear(t_toolbox *tools)
{
	free(tools->old_pwd);
	free(tools->home_dir);
	free(tools->pwd);
	free_arr(tools->env);
	tools_reload(tools);
	free(tools);
	return (exit_code());
}

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	m_exit(t_toolbox *tools, t_command *cmd)
{
	int	code;

	if (cmd->args)
	{
		if (cmd->args[1])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			g_exit_status = 1;
		}
		else
		{
			if (!check_num(cmd->args[0]))
			{
				code = ft_atoi(cmd->args[0]);
				printf ("code: %d\n", code);
				g_exit_status = code % 256;
				printf ("g_exit_status: %d\n", g_exit_status);
				return (exit_clear(tools));
			}
			else
				return (exit_num_err(tools));
		}
	}
	g_exit_status = 0;
	return (exit_clear(tools));
}
