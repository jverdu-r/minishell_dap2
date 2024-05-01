/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:17:51 by daparici          #+#    #+#             */
/*   Updated: 2024/03/18 23:00:54 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

void	print_arguments(char **arg, int i, int out_fd)
{
	while (arg[i])
	{
		//dprintf(2, "argument: %s\n", arg[i]);
		ft_putstr_fd(arg[i], out_fd);
		if (arg[i + 1])
			ft_putchar_fd(' ', out_fd);
		i++;
	}
}

int	ft_echo(t_command *cmd)
{
	int		flag;
	size_t	i;
	size_t	j;

	flag = 0;
	i = 0;
	if (cmd->args != NULL)
	{
		//dprintf(2, "fd_out: %i\n", cmd->out_fd);
		while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n", 2))
		{
			j = 1;
			while (cmd->args[i][j] && cmd->args[i][j] == 'n')
				j++;
			if (j != ft_strlen(cmd->args[i]) && cmd->args[i][j] != 'n')
				break ;
			flag = 1;
			i++;
		}
		if (cmd->args[i])
			print_arguments(cmd->args, i, cmd->out_fd);
		if (flag == 0)
			ft_putchar_fd('\n', cmd->out_fd);
	}
	return (EXIT_SUCCESS);
}
