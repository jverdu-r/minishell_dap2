/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:03:10 by daparici          #+#    #+#             */
/*   Updated: 2024/05/15 11:17:09 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	resolve_heredocs(t_command *cmd, char **env)
{
	t_command	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->heredoc)
		{
			check_here_doc(aux, env);
		}
		if (aux->next)
			aux = aux->next;
		else
			break ;
	}
}

void	check_here_doc(t_command *cmd, char **env)
{
	int		pipe1[2];
	int		i;
	int		pid;
	int		status;

	i = 0;
	while (cmd->limiter[i])
	{
		(sig_ignire(), pipe(pipe1));
		pid = fork();
		if (pid < 0)
			(perror("minishell:"), exit(1));
		if (pid == 0)
			child_control(pipe1, env, cmd, i);
		else
		{
			(close(pipe1[1]));
			if (cmd->limiter[i + 1])
				close(pipe1[0]);
			waitpid(pid, &status, 0);
			i++;
		}
	}
	if (cmd->limiter)
		cmd->heredoc = pipe1[0];
}

void	child_control(int *pipe1, char **env, t_command *cmd, int i)
{
	char	*line;
	char	*aux;
	char	*str_trimed;

	(sig_heredoc(), write(2, "> ", 2));
	str_trimed = trimmed(ft_strdup(cmd->limiter[i]), 0, 0);
	line = get_next_line(0);
	while (ft_strlen(str_trimed) != (ft_strlen(line) - 1)
		|| ft_strncmp(line, str_trimed, ft_strlen(str_trimed)))
	{
		if (line == NULL)
			(printf("\n"), exit(0));
		if (!ft_strcmp(str_trimed, cmd->limiter[i]))
			aux = expander_hdoc(line, env);
		else
			aux = line;
		write(2, "> ", 2);
		ft_putstr_fd(aux, pipe1[1]);
		free(aux);
		free(line);
		line = get_next_line(0);
	}
	(free(str_trimed), free(line), close(pipe1[1]), close(pipe1[0]));
	exit(0);
}

char	*find_variable(char *str, unsigned int i)
{
	unsigned int		j;
	char				*aux;

	j = i;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')))
		i++;
	aux = ft_substr(str, j, (i - j));
	return (aux);
}

char	*check_env(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, lenght_to_equal(env[i])) == 0)
			return (ft_substr(env[i], lenght_to_equal(env[i]) + 1,
					ft_strlen(env[i]) - lenght_to_equal(env[i]) + 1));
		i++;
	}
	return (ft_strdup(""));
}

// void	check_here_doc(t_command *cmd, char **env)
// {
// 	int		pipe1[2];
// 	char	*line;
// 	char	*aux;
// 	int		i;

// 	i = 0;
// 	while (cmd->limiter[i] && g_exit_status != 1)
// 	{
// 		pipe(pipe1);
// 		write(2, "> ", 2);
// 		line = get_next_line(0);
// 		while (ft_strlen(cmd->limiter[i]) != (ft_strlen(line) - 1)
// 			|| ft_strncmp(line, cmd->limiter[i], ft_strlen(cmd->limiter[i])))
// 		{
// 			if (g_exit_status == 1)
// 				break ;
// 			aux = expander_hdoc(line, env);
// 			write(2, "> ", 2);
// 			ft_putstr_fd(aux, pipe1[1]);
// 			free(aux);
// 			line = get_next_line(0);
// 		}
// 		if (g_exit_status == 1)
// 			break ;
// 		free(line);
// 		close(pipe1[1]);
// 		i++;
// 	}
// 	if (cmd->limiter)
// 		cmd->heredoc = pipe1[0];
// }
