/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:51:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 16:53:10 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	if (i == 2)
	{
		if (!ft_isnumber(args[1]))
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (1);
		}
		return (ft_atoi(args[1]));
	}
	return (0);
}
