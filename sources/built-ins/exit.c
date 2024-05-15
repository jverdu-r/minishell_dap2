/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:44:34 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/15 18:37:16 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_num_err(t_toolbox *tools)
{
	ft_putstr_fd("bash: exit: hola: numeric argument required\n", 2);
	free(tools->old_pwd);
	free(tools->home_dir);
	free(tools->pwd);
	free_arr(tools->env);
	tools_reload(tools);
	free(tools);
	return (exit_code(2));
}

int	exit_clear(t_toolbox *tools, int ex)
{
	free(tools->old_pwd);
	free(tools->home_dir);
	free(tools->pwd);
	free_arr(tools->env);
	tools_reload(tools);
	free(tools);
	return (exit_code(ex));
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

int	get_code(int code)
{
	if (code < 0)
		code = (code * -1) + 2;
	if (code > 255)
		code = code % 256;
	return (code);
}

int	m_exit(t_toolbox *tools, t_command *cmd)
{
	int	code;

	if (cmd->args)
	{
		if (cmd->args[1])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			return (exit_clear(tools, 2));
		}
		else
		{
			if (!check_num(cmd->args[0]))
			{
				code = ft_atoi(cmd->args[0]);
				code = get_code(code);
				printf("code: %d\n", code);
				return (exit_clear(tools, code));
			}
			else
				return (exit_num_err(tools));
		}
	}
	return (exit_clear(tools, 0));
}
