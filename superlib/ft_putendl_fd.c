/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:50:41 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/15 14:45:05 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./superlib.h"

int	ft_putendl_fd(char *s, int fd)
{
	char	c;

	c = '\n';
	if (!s)
		return (-1);
	if (ft_putstr_fd(s, fd))
		return (-1);
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}
