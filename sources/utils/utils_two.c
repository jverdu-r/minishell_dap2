/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:53:31 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/29 16:22:57 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

char	*fully_prompt(char *input, char c)
{
	char	*aux;
	char	*pipe;

	if (c == '|')
	{
		while (input[ft_strlen(input) - 1] == '|')
		{
			aux = readline(">");
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

void	sort_arr(char **arr)
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
				aux = arr[j];
				arr[j] = arr[i];
				arr[i] = aux;
			}
			j++;
		}
		i++;
	}
}
