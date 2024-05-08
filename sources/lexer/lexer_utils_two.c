/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:28:22 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/06 12:55:58 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer_length(t_lexer *list)
{
	int			i;
	t_lexer		*aux;

	if (!list)
		return (0);
	aux = list;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

void	lexer_free(t_lexer *list)
{
	t_lexer	*aux;

	if (list)
	{
		while (list)
		{
			if (list->str)
				free(list->str);
			aux = list;
			if (list->next)
			{
				list = list->next;
				free(aux);
			}
			else
				break ;
		}
	}
}

void	lexer_show(t_lexer *list)
{
	t_lexer	*tmp;

	tmp = list;
	printf("\n");
	while (tmp)
	{
		printf("---node---\n\n");
		if (tmp->str)
		{
			if (!ft_strcmp(tmp->str, " "))
				printf("space\n");
			else
				printf("str: %p, %s\n", tmp->str, tmp->str);
		}
		if (tmp->token)
			printf("token: %u, %d\n", tmp->token, tmp->token);
		printf("\n---end node---\n");
		tmp = tmp->next;
	}
	printf("\n");
}

int	*init_ct(int cr)
{
	int		*ct;

	ct = ft_calloc(sizeof(int), 3);
	ct[0] = 1;
	ct[1] = 1;
	ct[2] = cr;
	return (ct);
}
