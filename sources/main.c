/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:28:15 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/15 11:24:29 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_toolbox	*tools;

	//atexit(leaks);
	//g_exit_status = 0;
	if (argc != 1 || argv[1])
	{
		printf("Minishell must be executed wihtout arguments");
		exit(0);
	}
	tools = ft_calloc(sizeof(t_toolbox), 1);
	tools_load(tools);
	if (envp[0] == 0)
		tools->env = new_env();
	else
		tools->env = envp_dup(envp, tools);
	pwd_search(tools);
	minishell_loop(tools);
	free(tools);
	return (0);
}
