/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lim_trimmer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:43:46 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/22 17:50:43 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	trim_quotes(char **words, char **arr, int i)
{
	if (words[i][0] == '\"')
	{
		arr[i] = ft_substr(words[i], 1, ft_strlen(words[i]) - 2);
		i++;
	}
	else if (words[i][0] == '\'')
	{
		arr[i] = ft_substr(words[i], 1, ft_strlen(words[i]) - 2);
		i++;
	}
	return (i);
}

char	**get_words(char **words)
{
	char	**arr;
	int		i;

	i = 0;
	while (words[i])
		i++;
	arr = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (words[i])
	{
		if (words[i][0] == '\"' || words[i][0] == '\'')
			i = trim_quotes(words, arr, i);
		else
		{
			arr[i] = ft_strdup(words[i]);
			i++;
		}
	}
	return (arr);
}

int	get_qt(char *str, int *it, char **words)
{
	it[1] = 1;
	while (str[it[0] + it[1]] != str[it[0]] && str[it[0] + it[1]])
		it[1]++;
	words[it[2]] = ft_substr(str, it[0], it[1] + 1);
	it[2]++;
	return (it[0] + it[1]);
}

int	get_nqt(char *str, int *it, char **words)
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

char	*split_trim(char *str)
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
			it[0] = get_qt(str, it, words);
		else
			it[0] = get_nqt(str, it, words);
		it[0]++;
	}
	words[it[2]] = 0;
	res = get_trim(words);
	return (res);
}
