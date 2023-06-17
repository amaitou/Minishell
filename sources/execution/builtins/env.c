/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:47:55 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/17 18:33:31 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_usage(char **args)
{
	printf("minishell: env: %c%c: invalid option\n", args[1][0], args[1][1]);
	printf("env: usage: env\n");
	return (EXIT_FAILURE);
}

int	ft_env(char **env, t_parser *list)
{
	int	i;

	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (list->args[1] && list->args[1][0] == '-' && list->args[1][1])
		return (print_usage(list->args));
	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
