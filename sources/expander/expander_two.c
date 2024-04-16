/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:06 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/22 17:45:47 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exp_quotes(char **words, char **arr, char **env, int i)
{
	char	*aux;

	if (words[i][0] == '\"')
	{
		aux = ft_substr(words[i], 1, ft_strlen(words[i]) - 2);
		arr[i] = expander_hdoc(aux, env);
		//arr[i] = exp_word(aux, env);
		free(aux);
		i++;
	}
	else if (words[i][0] == '\'')
	{
		aux = ft_substr(words[i], 1, ft_strlen(words[i]) - 2);
		arr[i] = ft_strdup(aux);
		free(aux);
		i++;
	}
	return (i);
}

char	**exp_words(char **words, char **env)
{
	char	**arr;
	char	*aux;
	int		i;

	i = 0;
	while (words[i])
		i++;
	arr = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (words[i])
	{
		if (words[i][0] == '\"' || words[i][0] == '\'')
			i = exp_quotes(words, arr, env, i);
		else
		{
			aux = ft_strdup(words[i]);
			arr[i] = exp_word(aux, env);
			free(aux);
			i++;
		}
	}
	return (arr);
}

int	extract_qt(char *str, int *it, char **words)
{
	it[1] = 1;
	while (str[it[0] + it[1]] != str[it[0]] && str[it[0] + it[1]])
		it[1]++;
	words[it[2]] = ft_substr(str, it[0], it[1] + 1);
	it[2]++;
	return (it[0] + it[1]);
}

int	extract_nqt(char *str, int *it, char **words)
{
	it[1] = 0;
	while (str[it[0] + it[1]])
	{
		if (str[it[0] + it[1]] == '\'' || str[it[0] + it[1]] == '\"')
			break ;
		it[1]++;
	}
	words[it[2]] = ft_substr(str, it[0], it[1]);
	it[2]++;
	it[0] += it[1];
	return (it[0]);
}

char	*split_words(char *str, char **env)
{
	char	**words;
	int		it[3];
	char	*res;

	if (!str)
		return (NULL);
	it[0] = 0;
	it[1] = 0;
	it[2] = word_count(str);
	words = malloc(sizeof(char *) * (it[2] + 2));
	if (!words)
		return (NULL);
	it[2] = 0;
	while (it[0] < (int)ft_strlen(str) - 2 && str[it[0]])
	{
		if (str[it[0]] == '\'' || str[it[0]] == '\"')
			it[0] = extract_qt(str, it, words);
		else
			it[0] = extract_nqt(str, it, words);
		it[0]++;
	}
	words[it[2]] = 0;
	res = get_res(words, env);
	return (res);
}
