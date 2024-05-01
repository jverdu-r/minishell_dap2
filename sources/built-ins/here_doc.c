/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:03:10 by daparici          #+#    #+#             */
/*   Updated: 2024/03/21 14:25:14 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

void	resolve_heredocs(t_command *cmd, char **env)
{
	t_command	*aux;
	int			pid;
	int			status;

	father_workout();
	aux = cmd;
	pid = fork();
	if (pid < 0)
		(perror("minishell:"), exit(1));
	if (pid == 0)
	{
		sig_heredoc();
		while (aux)
		{
			if (aux->heredoc)
				check_here_doc(aux, env);
			if (aux->next)
				aux = aux->next;
			else
				break ;
		}
	}
	else
		waitpid(pid, &status, 0);
}

void	check_here_doc(t_command *cmd, char **env)
{
	int		pipe1[2];
	char	*line;
	char	*aux;
	int		i;

	i = 0;
	sig_heredoc();
	while (cmd->limiter[i])
	{
		pipe(pipe1);
		write(2, "> ", 2);
		line = get_next_line(0);
		while (ft_strlen(cmd->limiter[i]) != (ft_strlen(line) - 1)
			|| ft_strncmp(line, cmd->limiter[i],
				ft_strlen(cmd->limiter[i])))
		{
			aux = expander_hdoc(line, env);
			write(2, "> ", 2);
			ft_putstr_fd(aux, pipe1[1]);
			free(aux);
			line = get_next_line(0);
		}
		free(line);
		close(pipe1[1]);
		if (cmd->limiter[i + 1])
			close(pipe1[0]);
		i++;
	}
	if (cmd->limiter)
		cmd->heredoc = pipe1[0];
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

char	*expander_hdoc(char *str, char **env)
{
	unsigned int	i;
	char			*variable;
	char			*expand_str;
	char			*copy_ex_str;

	i = 0;
	expand_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\t'
			&& str[i + 1] != '\n' && str[i + 1])
		{
			if (!ft_strncmp(str, "$?", 2))
				return (ft_strjoin(ft_itoa(g_exit_status), "\n"));
			variable = find_variable(str, i + 1);
			copy_ex_str = expand_str;
			expand_str = ft_strjoin(copy_ex_str, check_env(variable, env));
			i++;
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0'
				&& str[i] <= '9')))
				i++;
		}
		else
		{
			copy_ex_str = expand_str;
			expand_str = ft_strjoin(copy_ex_str, ft_substr(str, i, 1));
			i++;
		}
	}
	return (expand_str);
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
			return(ft_substr(env[i], lenght_to_equal(env[i]) + 1,
					ft_strlen(env[i]) - lenght_to_equal(env[i]) + 1));
		i++;
	}
	return(ft_strdup(""));
}
