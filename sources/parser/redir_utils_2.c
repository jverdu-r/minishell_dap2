/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:19:34 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/06/05 13:43:45 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redir(t_command *cmd, char **env)
{
	t_command	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->in_files)
		{
			if (check_rd_str(aux->in_files, env))
				return (1);
		}
		if (aux->out_files)
		{
			if (check_rd_str(aux->out_files, env))
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
