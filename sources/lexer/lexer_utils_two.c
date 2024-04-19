/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:28:22 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/17 12:18:55 by jverdu-r         ###   ########.fr       */
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
	t_lexer *aux;


	if (list)
	{
		while (list)
		{
			if (list->str)
			{
				printf("list-> str: %p, '%s'\n",list->str, list->str);
				free(list->str);
			}
			aux = list;
			free(aux);
			if (list->next)
				list = list->next;
			else
				break ;
		}

		/*while (list->next)
		{
			if (list->str)
			{
				printf("list-> str: %p, '%s'\n",list->str, list->str);
				free(list->str);
			}
			list = list->next;
			if (list->prev)
				free(list->prev);
		}
		if (!list->next)
		{
			if (list->str)
			{
				printf("list-> str: %p, '%s'\n",list->str, list->str);
				free(list->str);
			}
		}
		free(list);*/
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
