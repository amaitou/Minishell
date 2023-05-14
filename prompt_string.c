/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:51 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/14 01:14:46 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*get_user(void)
{
	char	*user;
	char	*return_line;
	char	*cwd;

	user = getenv("USER");
	cwd = getcwd(NULL, PATH_MAX);
	return_line = string_join(ft_strdup("[\033[0;32m"), ft_strdup(user));
	return_line = string_join(return_line, ft_strdup("\033[0m\033[0;36m "));
	return_line = string_join(return_line, ft_strdup(ft_strrchr(cwd, '/') + 1));
	return_line = string_join(return_line, ft_strdup("\033[0m]$ "));
	return (return_line);
}

char	*prompt_string(void)
{
	if (getenv("USER") && getcwd(NULL, PATH_MAX))
		return (readline(get_user()));
	else
		return (readline("\033[0;36mminishell\033[0m]$ "));
}
