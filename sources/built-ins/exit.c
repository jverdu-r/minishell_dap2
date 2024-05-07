/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:30:53 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/07 18:09:44 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int m_exit(t_toolbox *tools, t_command *cmd)
{
    if (!cmd->args)
    {
	tools_reload(tools);
	free(tools);
	rl_clear_history();
	return(exit_code());
    }
    else
    {
	printf("minishell exit error: too many arguments\n");
	return (EXIT_FAILURE);
    }
}
