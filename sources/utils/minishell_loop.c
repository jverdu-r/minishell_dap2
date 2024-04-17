/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:14:37 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/03/21 14:00:21 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tools_reload(t_toolbox *tools)
{
	lexer_free(tools->lexer_list);
	if (tools->args)
		free(tools->args);
	tools->args = NULL;
	tools->lexer_list = NULL;
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
	printf("\nEXIT\n");
	rl_clear_history();
	exit(0);
}

int	minishell_loop(t_toolbox *tools)
{
	int		exit;

	while (1)
	{
		exit = 0;
		g_exit_status = 0;
		signals_workout();
		exit = check_input(tools);
		if (!tools->args && exit == 0)
			return (exit_code());
		else if (tools->args && ft_strcmp(tools->args, "") == 0)
		{
			free(tools->args);
		}
		else if (tools->args)
		{
			add_history(tools->args);
			if (!handle_quotes(tools->args))
			{
				token_reader(tools);
				if (!check_syntax(tools->lexer_list))
				{
					tools->cmd = parser(tools);
					expander(tools);
					get_fds(tools->cmd);
					cmd_show(tools->cmd);
					ft_executor(tools);
				}
			}
			tools_reload(tools);
		}
		//system("leaks minishell");
	}
	return (0);
}
