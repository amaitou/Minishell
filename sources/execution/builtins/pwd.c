/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:30:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 20:06:16 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(ft_perror("pwd: "));
	pwd = string_join(pwd, ft_strdup("\n"));
	if (ft_putstr_fd(pwd, STDOUT_FILENO) == -1)
		exit(ft_perror("pwd: "));
	free(pwd);
	exit(EXIT_SUCCESS);
}
