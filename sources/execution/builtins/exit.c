/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:51:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/19 21:04:11 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	numeric_arg_err(char *string)
{
	ft_putstr_fd("minishell: exit ", STDERR_FILENO);
	ft_putstr_fd(string, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required",
		STDERR_FILENO);
	return (255);
}

int	ft_exit(char **args, t_parser *list)
{
	int	i;

	i = -1;
	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	while (args[1] && args[1][++i])
		if (!ft_isdigit(args[1][i]))
			exit (numeric_arg_err(args[1]));
	if (!args[1])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(g_vars->exit_status);
	}
	else if (args[1] && !args[2])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit (ft_atoi(args[1]));
	}
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (EXIT_FAILURE);
}
