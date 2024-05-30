/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:27:16 by jorge             #+#    #+#             */
/*   Updated: 2024/05/30 19:17:12 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*get_cmd(t_command *cmd, t_lexer *list, char **env)
{
	char	*exp;

	if (list->str && list->token == 0)
		exp = expander(list->str, env, 0);
	else
		exp = NULL;
	while (list && ft_strlen(exp) < 1)
	{
		if (exp)
			free(exp);
		if (list->str && list->token == 0)
			exp = expander(list->str, env, 0);
		else
		{
			exp = NULL;
			break ;
		}
		list = list->next;
	}
	cmd->cmd = exp;
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
