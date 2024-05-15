/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:53:31 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/15 11:43:48 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fully_prompt(char *input, char c)
{
	char	*aux;
	char	*pipe;

	if (c == '|')
	{
		while (input[ft_strlen(input) - 1] == '|')
		{
			aux = get_input(readline(">"));
			pipe = input;
			input = ft_strjoin(pipe, aux);
			free(pipe);
			free(aux);
		}
	}
	return (input);
}

t_bool	switch_bool(t_bool bool)
{
	if (bool == FALSE)
		bool = TRUE;
	else
		bool = FALSE;
	return (bool);
}

char	**sort_arr(char **arr)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				printf("linea sin ordenar: %s\n", arr[i]);
				aux = arr[j];
				arr[j] = arr[i];
				arr[i] = aux;
				printf("linea ordenada: %s\n", arr[i]);
			}
			j++;
		}
		i++;
	}
	return (arr);
}

char	*get_home(void)
{
	char	*aux;
	char	*home;
	char	*dir;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	dir = getcwd(NULL, 0);
	while (dir[i[0]] && i[1] <= 2)
	{
		if (dir[i[0]] == '/')
			i[1]++;
		i[0]++;
	}
	aux = ft_substr(dir, 0, i[0]);
	home = ft_strjoin("HOME=", aux);
	free(aux);
	free(dir);
	return (home);
}

int	check_input_st(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '|')
		return (0);
	else
		return (1);
}
