/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:55:50 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/22 10:33:26 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ovarpass(char *str, int i)
{
	int	j;

	while (str[i] == '$')
		i++;
	while (str[i])
	{
		if (!isalpha(str[i]))
			break ;
		i++;
	}
	j = i;
	while (str[j])
	{
		if (ft_isdigit(str[j]))
			return (ft_strlen(str) - 1);
		j++;
	}
	i--;
	return (i);
}

int	*init_qt(void)
{
	int	*qt;

	qt = ft_calloc(sizeof(int), 2);
	qt[0] = 0;
	qt[1] = 0;
	return (qt);
}

char	*expnd(char *str, char **env)
{
	int		i;
	char	*aux;
	char	**r_var;

	aux = ft_strjoin(str, "=");
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], aux, ft_strlen(aux)))
		{
			r_var = ft_split(env[i], '=');
			free(aux);
			aux = ft_strdup(r_var[1]);
			free_arr(r_var);
			free(str);
			return (aux);
		}
		i++;
	}
	free(aux);
	aux = malloc(sizeof(char) * 1);
	aux[0] = 0;
	free(str);
	return (aux);
}

char	*init_aux(void)
{
	char	*aux;

	aux = ft_calloc(sizeof(char), 1);
	aux[0] = 0;
	return (aux);
}

char	*check_exp_redir(char *str, char **env)
{
	int		*qt;
	int		i;
	char	*res;

	qt = init_qt();
	i = 0;
	res = check_str_two(str, env, i, qt);
	free(qt);
	return (trimmed(res, 0, 0));
}
