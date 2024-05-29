/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:06:57 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/29 02:55:55 by jorge            ###   ########.fr       */
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

char	*expand(char *str, int i, char **env)
{
	char	*aux;
	char	*res;

	res = ft_strdup("");
	while (str[i] && str[i] != '\"')
	{
		aux = res;
		if (str[i] == '$' && str[i + 1])
		{
			res = var_exp(str, aux, i, env);
			i = ovarpass(str, i);
		}
		else
			res = charjoin(aux, str[i]);
		i++;
	}
	return (res);
}

char	*noqt(char *str, int i, char **env)
{
	char	*aux;
	char	*res;

	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			break ;
		aux = res;
		if (str[i] == '$' && str[i + 1])
		{
			res = var_exp(str, aux, i, env);
			i = ovarpass(str, i);
		}
		else
			res = charjoin(aux, str[i]);
		i++;
	}
	return (res);
}

char	*extract(char *str, int i)
{
	int		j;
	char	*res;

	j = i + 1;
	while (str[j] && str[j] != '\'')
		j++;
	j--;
	res = ft_substr(str, i + 1, j - i);
	return (res);
}

int	check_next(char *str, int i, char c)
{
	if (c == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		return (i);
	}
	if (c == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		return (i);
	}
	else
	{
		while (str[i])
		{
			if (str[i] == '\"' || str[i] == '\'')
				break ;
			i++;
		}
		return (i);
	}
}

char	*expansor(char *str, char **env)
{
	int		i;
	char	*aux;
	char	*res;
	char	*exp;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		aux = res;
		if (str[i] && str[i] == '\"')
		{
			exp = expand(str, i + 1, env);
			i = check_next(str, i, '\"');
			res = ft_strjoin(aux, exp);
			free(aux);
			free(exp);
			i++;
		}
		else if (str[i] && str[i] == '\'')
		{
			exp = extract(str, i);
			i = check_next(str, i, '\'');
			res = ft_strjoin(aux, exp);
			free(aux);
			free(exp);
			i++;
		}
		else if (str[i] && str[i] != '\'' && str[i] != '\"')
		{
			exp = noqt(str, i, env);
			i = check_next(str, i, 'c');
			res = ft_strjoin(aux, exp);
			free(aux);
			free(exp);
		}
	}
	return (res);
}
