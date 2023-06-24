/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:47:55 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/24 05:58:35 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_usage(char **args, int i)
{
	if (i)
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putchar_fd(args[1][0], STDERR_FILENO);
		ft_putchar_fd(args[1][1], STDERR_FILENO);
		ft_putendl_fd(" invalid option", STDERR_FILENO);
	}
	ft_putendl_fd("env: usage: env", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_env(char **env, t_parser *list)
{
	int	i;

	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (list->args[1] && list->args[1][0] == '-' && list->args[1][1])
		return (print_usage(list->args, 1));
	else if (list->args[1])
		return (print_usage(NULL, 0));
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
