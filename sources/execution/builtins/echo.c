/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:46:23 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/17 18:33:12 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_echo(char **args, t_parser *list)
{
	int	new_line;
	int	i;

	new_line = 0;
	i = 0;
	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	while (args[++i])
	{
		if (i == 1 && !ft_strncmp(args[i], "-n", ft_strlen("-n")))
			new_line = 1;
		else
		{
			if (ft_putstr_fd(args[i], STDOUT_FILENO) == -1)
				return (ft_perror("echo: "));
			if (args[i + 1])
				if (ft_putstr_fd(" ", STDOUT_FILENO) == -1)
					return (ft_perror("echo: "));
		}
	}
	if (!new_line)
		if (ft_putstr_fd("\n", STDOUT_FILENO) == -1)
			return (ft_perror("echo: "));
	return (EXIT_SUCCESS);
}
