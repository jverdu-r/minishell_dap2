/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:06:57 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/24 19:03:08 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_exp_value(char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str && str[i] != '=')
		i++;
	value = ft_substr(str, i + 1, ft_strlen(str) - 1);
	return (value);
}

int	ft_exp_stop(char c)
{
	if (c == '_' || c == '?' || \
		ft_isalpha(c) || ft_isdigit(c))
		return (0);
	else
		return (1);
}

char	*check_str_two(char *str, char **env, int i, int *qt)
{
	char	*aux;
	char	*res;

	res = ft_strdup("");
	while (str[i])
	{
		aux = res;
		if (str[i] == '\'' || str[i] == '\"')
			qt = switch_qt(qt, str[i]);
		if (qt[0] == 0 && qt[1] == 1)
			res = charjoin(aux, str[i]);
		if ((qt[0] == 0 && qt[1] == 0) || (qt[0] == 1 && qt[1] == 0))
		{
			if (str[i] == '$' && str[i + 1])
			{
				res = var_exp(str, aux, i, env);
				i = ovarpass(str, i);
			}
			else
				res = charjoin(aux, str[i]);
		}
		i++;
	}
	return (res);
}

char	*check_str(char *str, char **env)
{
	int		*qt;
	int		i;
	char	*aux;

	qt = init_qt();
	i = 0;
	aux = check_str_two(str, env, i, qt);
	free(qt);
	return (aux);
}
