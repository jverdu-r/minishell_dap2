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
	char	*exp;
	char	*res;

	res = ft_strdup("");
	while (str[i])
	{
		aux = res;
		if (str[i] == '\'' || str[i] == '\"')
			qt = switch_qt(qt, str[i]);
		if (qt[0] == 0 && qt[1] == 1)
			res = charjoin(aux, str[i]);
		if ((qt[0] == 0 && qt[1] == 0) || (qt[0] == 1 && qt[1] == 0))
		{
			if (str[i] == '$')
			{
				exp = var_find(str, i, env);
				res = ft_strjoin(aux, exp);
				free(exp);
				i = ovarpass(str, i);
			}
			else
				res = charjoin(aux, str[i]);
		}
		i++;
	}
	return (res);
}

char	*check_str(char *str, char **env)
{
	int		*qt;
	int		i;
	char	*res;
	char	*aux;

	qt = init_qt();
	i = 0;
	aux = check_str_two(str, env, i, qt);
	free(qt);
	free(str);
	res = trimmed(aux, 0, 0);
	return (res);
}

char	**check_args(char **args, char **env)
{
	int	i;
	char	**res;
	char	*aux;

	i = 0;
	while (args[i])
		i++;
	res = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (args[i])
	{
		aux = check_str(args[i], env);
		res[i] = ft_strdup(aux);
		free(aux);
		i++;
	}
	free(args);
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

	cmd = tools->cmd;
	while (cmd)
	{
		if (ft_strlen(cmd->cmd) > 2)
			cmd->cmd = check_str(cmd->cmd, tools->env);
		if (cmd->args)
			cmd->args = check_args(cmd->args, tools->env);
		if (cmd->in_files)
			check_redir(cmd->in_files, tools->env);
		if (cmd->out_files)
			check_redir(cmd->out_files, tools->env);
		cmd = cmd->next;
	}
}
