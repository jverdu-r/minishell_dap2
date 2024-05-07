/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:45:18 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/17 12:14:04 by jverdu-r         ###   ########.fr       */
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
			if (!list->next->str && list->token != PIPE)
				return (error_token(list->token));
			else if (list->token == PIPE && list->next->token == PIPE)
				return (error_token(list->token));
			else if (list->next->token == 0 && !list->next->str)
				return (error_token(list->token));
		}
		list = list->next;
	}
	return (0);
}
