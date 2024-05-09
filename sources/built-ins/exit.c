/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:30:53 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/08 18:00:11 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int m_exit(t_toolbox *tools, t_command *cmd)
{
    if (!cmd->args)
    {
        free(tools->old_pwd);
        free(tools->home_dir);
        free(tools->pwd);
        free_arr(tools->env);
	    tools_reload(tools);
	    free(tools);
	    return(exit_code());
    }
    else
    {
	    printf("minishell exit error: too many arguments\n");
	    return (EXIT_FAILURE);
    }
}
