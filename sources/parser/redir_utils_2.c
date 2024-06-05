/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:19:34 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/06/05 17:39:48 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redir(t_command *cmd, char **env)
{
	t_command	*aux;
	char		*exp;

	aux = cmd;
	exp = NULL;
	while (aux)
	{
		if (aux->in_files)
		{
			if (check_rd_str(aux->in_files, env, exp, 0) && !aux->next)
				return (1);
		}
		if (aux->out_files)
		{
			if (check_rd_str(aux->out_files, env, exp, 1) && !aux->next)
				return (1);
		}
		aux = aux->next;
	}
	return (0);
}

void	opn_cls(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(fd);
}
