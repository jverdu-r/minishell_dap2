/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:06:57 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/16 19:09:38 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_str_two(char *str, char **env, int i, int *qt)
{
	char	*aux;
	char	*res;

	aux = init_aux();
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			qt = switch_qt(qt, str[i]);
		if (qt[0] == 0 && qt[1] == 1)
			res = charjoin(aux, str[i]);
		if ((qt[0] == 0 && qt[1] == 0) || (qt[0] == 1 && qt[1] == 0))
		{
			if (str[i] == '$')
			{
				res = ft_strjoin(aux, var_find(str, i, env));
				i = ovarpass(str, i);
			}
			else
				res = charjoin(aux, str[i]);
		}
		free(aux);
		aux = res;
		i++;
	}
	return (res);
}

char	*check_str(char *str, char **env)
{
	int		*qt;
	int		i;
	char	*res;

	qt = init_qt();
	i = 0;
	res = check_str_two(str, env, i, qt);
	free(qt);
	free(str);
	return (trimmed(res, 0, 0));
}

char	**check_args(char **args, char **env)
{
	int	i;
	char	**res;

	i = 0;
	while (args[i])
		i++;
	res = ft_calloc(sizeof(char *), i);
	i = 0;
	while (args[i])
	{
		res[i] = check_str(args[i], env);
		i++;
	}
	free_arr(args);
	res[i] = 0;
	return (res);
}

void	check_redir(t_redir *lst, char **env)
{
	char	*aux;

	while (lst)
	{
		aux = lst->file;
		lst->file = check_exp_redir(aux, env);
		free(aux);
		lst = lst->next;
	}
}

void	expander(t_toolbox *tools)
{
	t_command	*cmd;
	int	i;

	cmd = tools->cmd;
	i = 0;
	while (cmd)
	{
		if (ft_strlen(cmd->cmd) > 2)
			cmd->cmd = check_str(cmd->cmd, tools->env);
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				cmd->args[i] = check_str(cmd->args[i], tools->env);
				i++;
			}
		}
		if (cmd->in_files)
			check_redir(cmd->in_files, tools->env);
		if (cmd->out_files)
			check_redir(cmd->out_files, tools->env);
		cmd = cmd->next;
	}
}
