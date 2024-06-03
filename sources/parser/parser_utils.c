/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:27:16 by jorge             #+#    #+#             */
/*   Updated: 2024/06/03 09:35:46 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

t_lexer	*get_cmd(t_command *cmd, t_lexer *list, char **env)
{
	char	*exp;

	if (list->str && list->token == 0)
		exp = expander(list->str, env, 0);
	while (list && ft_strlen(exp) < 1)
	{
		if (exp)
			free(exp);
		if (list->str && list->token == 0)
			exp = expander(list->str, env, 0);
		if (ft_strlen(exp) == 0 && !list->next->token)
			list = list->next;
		else
			break ;
	}
	if (ft_strlen(exp) > 0)
		cmd->cmd = exp;
	else
	{
		if (exp)
			free(exp);
		cmd->cmd = ft_strdup("");
	}
	return (list);
}

char	**cp_ad_args(char **args, char *str)
{
	char	**aux;
	int		i;

	i = 0;
	while (args[i])
		i++;
	aux = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (args[i])
	{
		aux[i] = ft_strdup(args[i]);
		i++;
	}
	aux[i] = str;
	aux[i + 1] = 0;
	free_arr(args);
	return (aux);
}

t_lexer	*extract_str(t_command *cmd, t_lexer *aux, char **env)
{
	if (!cmd->cmd && !aux->token)
		aux = get_cmd(cmd, aux, env);
	else
	{
		if (!cmd->args)
			aux = get_arg(cmd, aux, env);
		else
			aux = get_new_arg(cmd, aux, env);
	}
	return (aux);
}

int	check_rd_str(t_lexer *list, char **env)
{
	t_lexer	*aux;
	char	*exp;

	aux = list;
	exp = NULL;
	if (aux->token == LESS_LESS)
		return (0);
	else
	{
		aux = aux->next;
		if (aux && aux->str)
		{
			if (ft_strlen(aux->str) > 0)
			{
				exp = expander(aux->str, env, 0);
				if (ft_strlen(exp) > 0)
					return (free(exp), 0);
				else
					return (free(exp), 1);
			}
			else
				return (1);
		}
	}
	return (0);
}

t_command	*bad_redir(t_command *cmd, t_lexer *list)
{
	t_command	*aux;
	char		*msg;

	aux = NULL;
	list = list->next;
	if (ft_strlen(list->str) == 0)
		msg = ft_strdup("No such file or directory\n");
	else
		msg = ft_strjoin(list->str, ": ambiguous redirect\n");
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	free(msg);
	while (cmd->prev)
		cmd = cmd->prev;
	cmd_free(cmd);
	g_exit_status = 1;
	return (aux);
}
