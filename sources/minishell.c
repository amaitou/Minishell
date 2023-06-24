/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:56:29 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/24 08:03:17 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell			*minishell;

	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	g_vars = (t_vars *)malloc(sizeof(t_vars));
	g_vars->env = set_env(envp);
	while (1)
	{
		minishell = (t_minishell *)malloc(sizeof(t_minishell));
		if (initialize_minishell(minishell))
			return (printf("Failed to run minishell\n"));
		if (minishell->scanner->command == NULL)
			return (g_vars->exit_status);
		if (check_spaces(minishell->scanner->command))
			leaks_one(minishell);
		else
			__parse_and_execute__(minishell);
	}
	return (0);
}
