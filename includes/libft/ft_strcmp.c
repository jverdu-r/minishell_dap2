/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:49:07 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/05/14 18:41:18 by jverdu-r         ###   ########.fr       */
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
	return (res);
}
