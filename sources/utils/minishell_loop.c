/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:14:37 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/15 19:44:58 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

void	tools_reload(t_toolbox *tools)
{
	if (tools->lexer_list)
		lexer_free(tools->lexer_list);
	tools->lexer_list = NULL;
	if (tools->args)
		free(tools->args);
	tools->args = NULL;
	if (tools->cmd)
		cmd_free(tools->cmd);
	tools->cmd = NULL;
}

int	tools_load(t_toolbox *tools)
{
	tools->cmd = NULL;
	tools->lexer_list = NULL;
	return (1);
}

int	exit_code(int ex)
{
	printf("\nexit\n");
	rl_clear_history();
	exit(ex);
}

void	routine(t_toolbox *tools)
{
	tools->cmd = parser(tools);
	get_fds(tools->cmd);
	ft_executor(tools);
}

int	minishell_loop(t_toolbox *tools)
{
	while (1)
	{
		(signals_workout(), check_input(tools));
		if (tools->args && ft_strcmp(tools->args, "") == 0)
			free(tools->args);
		else if (tools->args)
		{
			add_history(tools->args);
			if (!handle_quotes(tools->args))
			{
				token_reader(tools);
				if (tools->lexer_list)
				{
					if (!check_syntax(tools->lexer_list))
						routine(tools);
				}
				else
					g_exit_status = 0;
			}
			tools_reload(tools);
		}
	}
	return (0);
}
