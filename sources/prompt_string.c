/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:59:13 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/19 13:03:43 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_user(t_prompt *prompt)
{
	char	*user;
	char	*cwd;

	user = getenv("USER");
	cwd = getcwd(NULL, 0);
	prompt->line = NULL;
	if (cwd == NULL)
	{
		prompt->line = ft_strdup("\033[0;36mminishell\033[0m]$ ");
		return ;
	}
	if (user)
		prompt->line = string_join(ft_strdup("[\033[0;32m"), ft_strdup(user));
	prompt->line = string_join(prompt->line,
			ft_strdup("\033[0m\033[1;37m@1337\033[0m\033[0;36m "));
	prompt->line = string_join(prompt->line,
			ft_strdup(ft_strrchr(cwd, '/') + 1));
	prompt->line = string_join(prompt->line, ft_strdup("\033[0m]$ "));
	free(cwd);
}

char	*prompt_string(t_prompt *prompt)
{
	get_user(prompt);
	return (readline(prompt->line));
}
