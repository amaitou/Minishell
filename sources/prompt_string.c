/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:51 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/18 21:49:52 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_user(t_prompt *prompt)
{
	char	*user;
	char	*cwd;

	user = getenv("USER");
	cwd = getcwd(NULL, PATH_MAX);
	prompt->line = string_join(ft_strdup("[\033[0;32m"), ft_strdup(user));
	prompt->line = string_join(prompt->line,
			ft_strdup("\033[0m\033[1;37m@1337\033[0m\033[0;36m "));
	prompt->line = string_join(prompt->line, ft_strdup(ft_strrchr(cwd, '/') + 1));
	prompt->line = string_join(prompt->line, ft_strdup("\033[0m]$ "));
	free(cwd);
}

char	*prompt_string(t_prompt *prompt)
{
	if (getenv("USER"))
	{
		get_user(prompt);
		return (readline(prompt->line));
	}
	else
		return (readline("\033[0;36mminishell\033[0m]$ "));
}
