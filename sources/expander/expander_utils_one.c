/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:21:11 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/22 17:49:11 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

int	*switch_qt(int *qt, char c)
{
	if (c == '\'')
	{
		if (qt[1] == 0 && qt[0] == 0)
			qt[1] = 1;
		else if (qt[1] == 1 && qt[0] == 0)
			qt[1] = 0;
	}
	if (c == '\"')
	{
		if (qt[1] == 0 && qt[0] == 0)
			qt[0] = 1;
		else if (qt[1] == 0 && qt[0] == 1)
			qt[0] = 0;
	}
	return (qt);
}

char	*trimmed(char *str, int i, int j)
{
	char	c;
	char	*res;

	res = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				res[j++] = str[i++];
			i++;
		}
		else
		{
			res[j] = str[i];
			i++;
			j++;
		}
	}
	res[j] = 0;
	free(str);
	return (res);
}

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

char	*var_find(char *str, int i, char **env)
{
	char	*aux;
	char	*res;

	
	i++;
	aux = ft_calloc(sizeof(char), 1);
	aux[0] = 0;
	while (str[i] && !is_space(str[i]) && str[i] != '$' \
		&& str[i] != '\"' && str[i] != '\'')
	{
		res = charjoin(aux, str[i]);
		aux = res;
		i++;
	}
	if (!ft_strncmp(res, "?", 1))
		res = ft_itoa(g_exit_status);
	else
		res = expnd(aux, env);
	return (res);
}

char	*charjoin(char *str, char c)
{
	char	*res;
	int	len;
	int	i;

	len = ft_strlen(str);
	res = ft_calloc(sizeof(char), len + 2);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = 0;
	free(str);
	return (res);
}