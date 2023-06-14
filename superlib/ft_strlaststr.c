/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlaststr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:39:01 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 13:39:05 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./superlib.h"

int	ft_strlaststr(const char *string1, const char *string2)
{
	int	i;
	int	j;

	if (!ft_strlen(string1) || !ft_strlen(string2)
		|| ft_strlen(string1) < ft_strlen(string2))
		return (0);
	i = ft_strlen(string1) - ft_strlen(string2);
	j = 0;
	while (string1[i])
	{
		if (string1[i] != string2[j])
			return (0);
		j++;
		i++;
	}
	return (1);
}
