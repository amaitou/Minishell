/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:46:23 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/19 12:37:52 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	should_print_newline(char *string)
{
	int	i;

	i = 0;
	if (string[i] != '-')
		return (0);
	i++;
	while (string[i])
	{
		if (string[i] != 'n')
			return (0);
		else if (string[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

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
		if (i == 1 && should_print_newline(args[i]))
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
