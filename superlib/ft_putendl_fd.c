/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:50:41 by amait-ou          #+#    #+#             */
/*   Updated: 2023/01/24 00:08:11 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./superlib.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	c;

	c = '\n';
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, &c, 1);
}