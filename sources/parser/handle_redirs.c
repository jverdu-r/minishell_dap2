/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:22:42 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/03/19 00:04:47 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

int	check_in_fd(t_redir *redir)
{
	t_redir	*in_files;

	in_files = redir;
	while (in_files)
	{
		if (access(in_files->file, R_OK) == -1)
		{
			if (errno == EACCES)
				error_msg("Access denied\n");
			else if (errno == ENOENT)
				error_msg("File does not exist\n");
			else
				error_msg("Access error\n");
		}
		if (in_files->next)
			in_files = in_files->next;
		else
			break ;
	}
	return (open(in_files->file, O_RDONLY));
}

void	check_out_fd(t_command *cmd)
{
	t_redir	*out_files;

	out_files = cmd->out_files;
	
	while (out_files)
	{
		if (cmd->app == 1)
		{
			cmd->out_fd  = open(out_files->file, O_WRONLY | O_APPEND 
				| O_CREAT, 0644);
		}
		else
		{
			cmd->out_fd = open(out_files->file, O_CREAT | O_WRONLY
					| O_TRUNC, 0644);
		}
		if (out_files->next)
			close(cmd->out_fd);
		if (out_files->next)
			out_files = out_files->next;
		else
			break;
	}
}

void	get_fds(t_command *raw_cmd)
{
	t_command	*cmd;

	cmd = raw_cmd;
	while (cmd)
	{
		if (cmd->in_files)
			cmd->in_fd = check_in_fd(cmd->in_files);
		if (cmd->out_files)
			check_out_fd(cmd);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}
