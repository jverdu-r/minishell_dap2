/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:28:15 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/13 20:06:39 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_toolbox	*tools;

	//atexit(leaks);
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
