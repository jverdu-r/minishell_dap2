/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:27:31 by daparici          #+#    #+#             */
/*   Updated: 2023/12/08 00:44:53 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern sig_atomic_t	g_exit_status;

int	ft_pwd(void)
{
	char	*buffer;
	char	*current_directory;

	buffer = (char *)malloc(PATH_MAX);
	if (buffer == NULL)
	{
		perror("Error en la asignacion de memoria");
		exit(EXIT_FAILURE);
	}
	current_directory = getcwd(buffer, PATH_MAX);
	if (current_directory == NULL)
	{
		perror("Error al obtener el directorio actual");
		free(buffer);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(current_directory, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(buffer);
	return (EXIT_SUCCESS);
}
