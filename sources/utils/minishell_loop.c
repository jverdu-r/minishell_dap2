/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:14:37 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/13 19:23:39 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

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

int	exit_code(void)
{
	printf("\nexit\n");
	rl_clear_history();
	exit(0);
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
		g_exit_status = 0;
		signals_workout();
		check_input(tools);
		if (tools->args && ft_strcmp(tools->args, "") == 0)
			free(tools->args);
		else if (tools->args)
		{
			add_history(tools->args);
			if (!handle_quotes(tools->args))
			{
				token_reader(tools);
				if (!check_syntax(tools->lexer_list))
					routine(tools);
			}
			tools_reload(tools);
		}
	}
	return (0);
}
