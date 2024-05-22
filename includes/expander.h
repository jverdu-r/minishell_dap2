/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:59:56 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/22 16:34:53 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft/libft.h"
# include "structs.h"
# include "minishell.h"

void	expander(t_toolbox *tools);
char	*charjoin(char *str, char c);
char	*var_find(char *str, int i, char **env);
char	*trimmed(char *str, int i, int j);
int		*switch_qt(int *qt, char c);
int		ovarpass(char *str, int i);
char	*expnd(char *str, char **env);
int		*init_qt(void);
char	*init_aux(void);
char	*check_exp_redir(char *str, char **env);
char	*check_str_two(char *str, char **env, int i, int *qt);
char	*var_exp(char *str, char *aux, int i, char **env);
char	*check_str(char *str, char **env);
void	check_voids(t_command *cmd);
int		ft_exp_stop(char c);
char	*get_exp_value(char *str);
#endif