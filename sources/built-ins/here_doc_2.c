/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:45:25 by daparici          #+#    #+#             */
/*   Updated: 2024/05/08 18:37:02 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

int	expander_hdoc_2(char *str, int i)
{
	i++;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0'
				&& str[i] <= '9')))
		i++;
	return (i);
}

char	*expander_hdoc_3(char *str, char **env, char *expand_str, int i)
{
	char	*variable;
	char	*copy_ex_str;

	if (!ft_strncmp(str, "$?", 2))
		return (ft_strjoin(ft_itoa(g_exit_status), "\n"));
	variable = find_variable(str, i + 1);
	copy_ex_str = expand_str;
	expand_str = ft_strjoin(copy_ex_str, check_env(variable, env));
	return (expand_str);
}

char	*expander_hdoc(char *str, char **env)
{
	int				i;
	char			*expand_str;
	char			*copy_ex_str;
	char			*aux;

	i = 0;
	expand_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\t'
			&& str[i + 1] != '\n' && str[i + 1])
		{
			copy_ex_str = expand_str;
			expand_str = expander_hdoc_3(str, env, copy_ex_str, i);
			i = expander_hdoc_2(str, i);
		}
		else
		{
			copy_ex_str = expand_str;
			aux = ft_substr(str, i, 1);
			expand_str = ft_strjoin(copy_ex_str, aux);
			free(copy_ex_str);
			free(aux);
			i++;
		}
	}
	return (expand_str);
}
