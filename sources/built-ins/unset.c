/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:50:15 by daparici          #+#    #+#             */
/*   Updated: 2023/12/12 18:28:17 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

int     ft_check_equal(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
        {
            export_error(arg);
            return (1);
        }
        i++;
    }
    return (0);
}

int 	ft_unset(t_toolbox *tools)
{
    int i;
    int j;
    char **tmp;

    i = 0;
    if (tools->cmd->args)
    {
        while (tools->cmd->args[i])
        {
            j = 0;
            while (tools->env[j])
            {
                if (!check_parametres(tools->cmd->args[i]) && !ft_check_equal(tools->cmd->args[i]))
                {
                    if (!ft_strncmp(tools->env[j], tools->cmd->args[i], lenght_to_equal(tools->cmd->args[i])))
                    {
                        tmp = delete_variable(tools->env, j);
                        free(tools->env);
                        tools->env = tmp;
                    }
                }
                else
                    break ;
                j++;
            }
            i++;
        }
    }
    return (EXIT_SUCCESS);
}

char    **delete_variable(char **env, int i)
{
    char    **env_copy;
    int     j;
    int     k;

    j = 0;
    k = 0;
    while (env[j])
        j++;
    env_copy = ft_calloc(sizeof(char *), j);
    if (!env_copy)
        return(NULL);
    j = 0;
    while (env[j])
    {
        if (j == i)
        {
            free(env[j]);
            j++;
        }
        env_copy[k] = env[j];
        j++;
        k++;
    }
    env_copy[k] = 0;
    return(env_copy);
}