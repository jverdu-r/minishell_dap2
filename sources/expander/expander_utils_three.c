/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_three.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jverdu-r@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:42:22 by jverdu-r         #+#    #+#             */
/*   Updated: 2024/05/07 10:42:23 by jverdu-r        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_exp(char *str, char *aux, int i, char **env)
{
	char	*exp;
	char	*res;

	exp = var_find(str, i, env);
	res = ft_strjoin(aux, exp);
	free(aux);
	free(exp);
	return (res);
}
