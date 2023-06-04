/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma    		+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:12:17 by amait-ou          #+#    #+#             */
/*   Updated: 2022/10/06 22:09:09 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./superlib.h"

char	*ft_strtrim(char const *s1, char c)
{
	int		begin;
	int		last;
	char	*p;

	if (!s1)
		return ((void *)0);
	last = ft_strlen(s1) - 1;
	begin = 0;
	p = (char *)s1;
	while (p[begin] && p[begin] == c)
		++begin;
	while (last > 0 && p[last] == c)
		last--;
	if (last < begin)
		return (ft_substr(p, begin, 0));
	return (ft_substr(p, begin, (last - begin) + 1));
}
