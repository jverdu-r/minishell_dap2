/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:30:53 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/13 20:13:05 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	g_exit_status;

#include "../../includes/minishell.h"

int m_exit(t_toolbox *tools, t_command *cmd)
{
    int    code;
    
    if (cmd->args)
    {
        if (cmd->args[1])
        {
        ft_putstr_fd("bash: exit: too many arguments\n", 2);
        g_exit_status = 1;
        }
        else
        {
            code = ft_atoi(cmd->args[0]);
            if (code > 255)
                g_exit_status = code % 255;
            else
                g_exit_status = code;
            printf("status: %d\n", g_exit_status);
        }
    }
    free(tools->old_pwd);
    free(tools->home_dir);
    free(tools->pwd);
    free_arr(tools->env);
	tools_reload(tools);
	free(tools);
	return(exit_code());
}
