/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorge <jorge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:32:32 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/15 11:17:27 by jorge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_msg(char *msg)
{
	printf("ERROR: %s", msg);
	return (-1);
}

int	error_token(t_token token)
{
	printf("%iminishell: sintax error near unexpected ", STDERR_FILENO);
	if (token == PIPE)
		printf("'|'%i\n", STDERR_FILENO);
	if (token == LESS)
		printf("'<'%i\n", STDERR_FILENO);
	if (token == LESS_LESS)
		printf("'<<'%i\n", STDERR_FILENO);
	if (token == GREAT)
		printf("'>'%i\n", STDERR_FILENO);
	if (token == GREAT_GREAT)
		printf("'>>'%i\n", STDERR_FILENO);
	return (-1);
}
