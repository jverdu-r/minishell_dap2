/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:59:56 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/03/19 20:31:47 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

#include "libft/libft.h"
#include "structs.h"
#include "minishell.h"

void    expander(t_toolbox *tools);
char *charjoin(char *str, char c);
char *var_find(char *str, int i, char **env);
int	is_space(char c);
char *trimmed(char *str, int i, int j);
int *switch_qt(int *qt, char c);
int	ovarpass(char *str, int i);
char	*expnd(char *str, char **env);
int *init_qt(void);
char	*expnd(char *str, char **env);
char *init_aux(void);
#endif