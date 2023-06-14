/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:46:23 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 18:38:55 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 0;
	i = 0;
	while (args[++i])
	{
		if (i == 1 && !ft_strcmp(args[i], "-n"))
			new_line = 1;
		else
		{
			if (ft_putstr_fd(args[i], STDOUT_FILENO) == -1)
				exit(ft_perror("echo: "));
			if (args[i + 1])
				if (ft_putstr_fd(" ", STDOUT_FILENO) == -1)
					exit(ft_perror("echo: "));
		}
	}
	if (!new_line)
		if (ft_putstr_fd("\n", STDOUT_FILENO) == -1)
			exit(ft_perror("echo: "));
	exit(EXIT_SUCCESS);
}
