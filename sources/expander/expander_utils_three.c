/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_three.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jverdu-r@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:42:22 by jverdu-r         #+#    #+#             */
/*   Updated: 2024/05/09 10:10:25 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_exp(char *str, char *aux, int i, char **env)
{
	char	*exp;
	char	*res;

	exp = var_find(str, i, env);
	res = ft_strjoin(aux, exp);
	free(aux);
	free(exp);
	return (res);
}

int check_void(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (1);
    else
    {
        while (is_space(str[i]))
            i++;
	    if  (str[i] == 0)
            return (1);
    }
    return (0);
}

int arr_len(char **arr)
{
    int i;
    int len;

    i = 0;
    len = 0;
        while(arr[i++])
    {
        if(!check_void(arr[i]))
            len++;
    }
    return (len);
}

char **check_void_args(char **args)
{
    char **arr;
    int     len;
    int     i;

    len = arr_len(args);
    i = 0;
    arr = ft_calloc(sizeof(char *), len + 2);
    if (!arr)
        return (NULL);
    i = 0;
    len = 0;
    while(args[i])
    {
        if(check_void(args[i]) < 1)
        {
            printf("entra\n");
            arr[len] = ft_strdup(args[i]);
            len++;
        }
        i++;
    }
    free_arr(args);
    arr[len] = 0;
    return(arr);
}

void	check_voids(t_command *cmd)
{
   t_command    *aux;

   while(cmd)
   {
       if (!check_void(cmd->cmd))
       {
            if (cmd->prev)
            {
                aux = cmd;
                cmd->prev->next = cmd->next;
                cmd = cmd->next;
                cmd->prev = aux->prev;
                scmd_free(aux);
            }
       }
       cmd->args = check_void_args(cmd->args);
       cmd = cmd->next;
   }
}
