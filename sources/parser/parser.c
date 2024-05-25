/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:38:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/25 16:47:39 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*cmd_list(t_lexer *list)
{
	t_command	*cmd;
	t_lexer		*aux;

	cmd = NULL;
	aux = list;
	while (aux)
	{
		if (aux->prev == NULL || aux->prev->token == PIPE)
			comm_addback(&cmd, init_cmd());
		aux = aux->next;
	}
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	return (cmd);
}

t_lexer	*redir_add(t_command *cmd, t_lexer *list)
{
	if (list->token == LESS)
		redir_addback(&cmd->in_files, \
			redir_new(trimmed(list->next->str, 0, 0)));
	if (list->token == GREAT || list->token == GREAT_GREAT)
	{
		redir_addback(&cmd->out_files, \
			redir_new(trimmed(list->next->str, 0, 0)));
		if (list->token == GREAT_GREAT)
			cmd->app = 1;
		else
			cmd->app = 0;
	}
	if (list->token == LESS_LESS)
	{
		cmd->limiter = lim_add(cmd->limiter, \
			cmd->heredoc, list->next->str);
		cmd->heredoc++;
	}
	list = list->next;
	return (list);
}

void	get_arg(t_command *cmd, char *str)
{
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		cmd->args = NULL;
	cmd->args[0] = trimmed(str, 0, 0);
	cmd->args[1] = 0;
}

void	get_new_arg(t_command *cmd, char *str)
{
	char	**aux;
	int		i;

	i = 0;
	while (cmd->args[i])
		i++;
	aux = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (cmd->args[i])
	{
		aux[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	aux[i] = trimmed(str, 0, 0);
	aux[i + 1] = 0;
	free_arr(cmd->args);
	cmd->args = aux;
}

t_command	*parser(t_toolbox *tools)
{
	t_lexer		*aux;
	t_command	*cmd;

	aux = tools->lexer_list;
	cmd = cmd_list(aux);
	while (aux)
	{
		if (aux->token == PIPE)
			cmd = cmd->next;
		else if (aux->token > 1)
			aux = redir_add(cmd, aux);
		else if (!cmd->cmd && !aux->token)
			cmd->cmd = ft_strdup(aux->str);
		else
		{
			if (!cmd->args)
				get_arg(cmd, aux->str);
			else
				get_new_arg(cmd, aux->str);
		}
		aux = aux->next;
	}
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}
