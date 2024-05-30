/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:46:24 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/30 09:25:34 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	read_words(char *args, int i, t_lexer **list)
{
	int	j;
	int	qt;

	j = 0;
	(void)list;
	while (args[i + j])
	{
		if (args[i + j] == '\'' || args[i + j] == '\"')
		{
			qt = i + j;
			j++;
			while (args[i + j] != args[qt])
				j++;
		}
		if (is_white_space(args[i + j]) || check_token(args, i + j))
			break ;
		else
			j++;
	}
	lexer_addback(list, lexer_new(ft_substr(args, i, j), 0));
	if (!list)
		return (-1);
	return (j);
}

char	*create_msg(char *str)
{
	char	*aux;
	char	*res;

	aux = ft_substr(str, 1, ft_strlen(str) - 2);
	res = ft_strjoin(aux, " : Command not found\n");
	free(aux);
	return (res);
}

int	ck_list_one(t_lexer *list)
{
	int		i;
	char	*msg;

	i = 0;
	msg = create_msg(list->str);
	while (list->str[i])
	{
		if (is_white_space(list->str[i]))
			i++;
		else if (list->str[i] == '\'' || list->str[i] == '\"')
			i++;
		else
			return (free(msg), 1);
	}
	return (ft_putstr_fd(msg, 2), free(msg), 0);
	return (free(msg), 1);
}

int	token_reader(t_toolbox *tools)
{
	t_token	tk;
	int		i;
	int		j;

	i = 0;
	while (tools->args[i])
	{
		j = 0;
		if (is_white_space(tools->args[i]))
			i++;
		if (check_token(tools->args, i))
		{
			tk = token_handler(tools, i);
			j += tk;
		}
		else
			j += read_words(tools->args, i, &tools->lexer_list);
		i += j;
	}
	if (ck_list_one(tools->lexer_list))
		return (0);
	else
		return (1);
}
