/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:30:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/16 12:17:20 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(t_parser *list)
{
	char	*pwd;

	if (list->type != __PIPE)
		if (redirections_handle(list->file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
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
