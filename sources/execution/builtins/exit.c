/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:51:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/18 09:57:19 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	numeric_arg_err(char *string)
{
	printf("minishell: exit %s: numeric argument required\n", string);
	return (255);
}

int	ft_exit(char **args, t_parser *list, t_vars *vars)
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
		exit(vars->exit_status);
	else if (args[1] && !args[2])
		exit (ft_atoi(args[1]));
	printf("minishell: exit: too many arguments\n");
	return (EXIT_FAILURE);
}
