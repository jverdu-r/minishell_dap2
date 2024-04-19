/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:55:50 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/16 19:26:12 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ovarpass(char *str, int i)
{
	while (!is_space(str[i]) && str[i] != '\"' \
		&& str[i] != '\'' && str[i])
		i++;
	if (str[i] == '\"' || str[i] == '\'' || is_space(str[i]))
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
	char	*aux;
	char	**r_var;
	int	i;

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
			return (aux);
		}
		i++;
	}
	free(aux);
	aux = malloc(sizeof(char) * 1);
	aux[0] = 0;
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
