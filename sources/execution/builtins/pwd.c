/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:30:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/19 12:10:12 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_usage(char **args)
{
	ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
	ft_putchar_fd(args[1][0], STDERR_FILENO);
	ft_putchar_fd(args[1][1], STDERR_FILENO);
	ft_putendl_fd(" invalid option", STDERR_FILENO);
	ft_putendl_fd("pwd: usage: pwd", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_pwd(char **args, t_parser *list)
{
	char	*pwd;

	if (list->prev->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (args[1] && args[1][0] == '-' && args[1][1])
		return (print_usage(args));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_perror("pwd: "));
	pwd = string_join(pwd, ft_strdup("\n"));
	if (ft_putstr_fd(pwd, STDOUT_FILENO) == -1)
	{
		free(pwd);
		return (ft_perror("pwd: "));
	}
	free(pwd);
	return (EXIT_SUCCESS);
}
