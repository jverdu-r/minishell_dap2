/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:46:24 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/27 18:31:21 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
			|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	get_quoted(char *args, t_lexer **list, int cr)
{
	char	cqt;
	int	ct[3];

	ct[0] = 1;
	ct[1] = 1;
	ct[2] = cr;
	cqt = args[cr];
	while (args[ct[2] + ct[0]])
	{
		if (ct[1] == 0 && (args[ct[2] + ct[0]] == '\"' \
			|| args[ct[2] + ct[0]] == '\''))
		{
			cqt = args[ct[2] + ct[0]];
			ct[1] = 1;
		}
		else if (args[ct[2] + ct[0]] == cqt)
			ct[1] = 0;
		if (ct[1] == 0 && is_white_space(args[ct[2] + ct[0]]))
			break ;
		ct[0]++;
	}
	lexer_addback(list, \
		lexer_new(ft_substr(args, cr, ct[0] + 1), 0));
	cr += ct[0] + 1;
	return (cr);
}

int	get_unquoted(char *args, t_lexer **list, int cr)
{
	int	ct;

	ct = 0;
	while (args[cr + ct] && !is_white_space(args[cr + ct]) && \
		!check_token(args, cr + ct))
		ct++;
	lexer_addback(list, \
		lexer_new(ft_substr(args, cr, ct), 0));
	cr += ct;
	return (cr);
}

void	read_words(char *args, t_lexer **list)
{
	int	cr;

	cr = 0;
	while (args[cr])
	{
		if (args[cr] == '\"' || args[cr] == '\'')
			cr = get_quoted(args, list, cr);
		else if (check_token(args, cr))
		{
			lexer_addback(list, \
				lexer_new(NULL, check_token(args, cr)));
			if (check_token(args, cr) == GREAT_GREAT || \
					check_token(args, cr) == LESS_LESS)
				cr = cr + 2;
			else
				cr++;
		}
		else if (is_white_space(args[cr]))
			cr++;
		else
			cr = get_unquoted(args, list, cr);
	}
}

int	token_reader(t_toolbox *tools)
{
	read_words(tools->args, &tools->lexer_list);
	return (0);
}
