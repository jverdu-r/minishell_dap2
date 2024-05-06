/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:49:07 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/03/20 20:14:57 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;
	int	res;

	a = 0;
	if (!s1 || !s2)
	{
		return (1);
	}
	while (s1[a] != 0 && s2[a] != 0 && s1[a] == s2[a])
	{
		a++;
	}
	res = s1[a] - s2[a];
	return ((unsigned char)res);
}
