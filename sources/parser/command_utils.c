/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:48:17 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/22 17:18:11 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*init_cmd(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->cmd = NULL;
	cmd->heredoc = 0;
	cmd->app = 0;
	cmd->append = NULL;
	cmd->limiter = NULL;
	cmd->args = NULL;
	cmd->in_fd = 0;
	cmd->in_files = NULL;
	cmd->out_fd = 1;
	cmd->out_files = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	comm_addback(t_command **head, t_command *new)
{
	t_command	*aux;

	aux = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new;
		new->prev = aux;
	}
}

void	cmd_show(t_command *cmd)
{
	t_command	*aux;
	t_redir		*in_aux;
	t_redir		*out_aux;
	int			i;

	aux = cmd;
	while (aux)
	{
		if (aux->cmd)
			printf("command: %s\n", aux->cmd);
		if (aux->append)
			printf("append to: %s\n", aux->append);
		if (aux->limiter)
		{
			i = 0;
			while (cmd->limiter[i])
			{
				printf("heredoc[%d] with limiter: %s\n", i, aux->limiter[i]);
				i++;
			}
		}
		if (aux->args)
		{
			i = 0;
			while (aux->args[i])
			{
				printf("argument[%d]: %s\n", i, aux->args[i]);
				i++;
			}
		}
		if (aux->out_fd)
			printf("out fd: %d\n", aux->out_fd);
		if (aux->in_fd)
			printf("in fd: %d\n", aux->in_fd);
		if (aux->out_files)
		{
			out_aux = aux->out_files;
			while (out_aux)
			{
				printf("out_file: %s\n", out_aux->file);
				out_aux = out_aux->next;
			}
		}
		if (aux->in_files)
		{
			in_aux = aux->in_files;
			while (in_aux)
			{
				printf("in_file: %s\n", in_aux->file);
				in_aux = in_aux->next;
			}
		}
		printf("have to append: %d\n", aux->app);
		aux = aux->next;
	}
}

void	scmd_free(t_command *cmd)
{
	cmd->out_fd = 0;
	cmd->in_fd = 0;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
		free_arr(cmd->args);
	if (cmd->limiter)
		free_arr(cmd->limiter);
	if (cmd->append)
		free(cmd->append);
	if (cmd->in_files != NULL)
		redir_free(cmd->in_files);
	if (cmd->out_files != NULL)
		redir_free(cmd->out_files);
	free(cmd);
}

void	cmd_free(t_command *cmd)
{
	while (cmd->next)
	{
		cmd = cmd->next;
		scmd_free(cmd->prev);
		cmd->prev = NULL;
	}
	scmd_free(cmd);
}
