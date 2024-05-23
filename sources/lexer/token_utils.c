/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:45:18 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/23 16:46:40 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_lstr(t_lexer *list)
{
	char	*aux;

	if (ft_strlen(list->str) == 2)
	{
		if (list->str[0] == '\'' || list->str[0] == '\"')
		{
			aux = malloc(sizeof(char *) * 1);
			aux[0] = 0;
			free(list->str);
			list->str = aux;
		}
	}
}

int	check_syntax(t_lexer *tk_list)
{
	t_lexer	*list;

	list = tk_list;
	while (list)
	{
		if (list->str)
			check_lstr(list);
		if (list->token)
		{
			if (list->token != PIPE && !list->next->str)
				return (error_token(list->token));
			else if (list->token == PIPE && list->next->token == PIPE)
				return (error_token(list->token));
			else if (list->token > 0 && !list->next->str)
				return (error_token(list->token));
		}
		list = list->next;
	}
	return (0);
}

void	token_expander(t_toolbox *tools)
{
	t_lexer	*aux;
	t_lexer	*list;
	char	*exp;

	aux = NULL;
	list = tools->lexer_list;
	while (list)
	{
		if (list->token == 0)
		{
			exp = check_str(list->str, tools->env);
			if (ft_strlen(exp) > 0)
				lexer_addback(&aux, lexer_new(exp, 0));
			else
				free(exp);
		}
		else
			lexer_addback(&aux, lexer_new(NULL, list->token));
		list = list->next;
	}
	lexer_free(tools->lexer_list);
	if (aux && aux->token == PIPE)
		aux = aux->next;
	tools->lexer_list = aux;
}
