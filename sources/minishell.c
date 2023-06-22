/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/22 17:01:42 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell			*minishell;
	struct sigaction	sigact;

	(void)argc;
	(void)argv;
	sigact.sa_sigaction = signal_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	g_vars = (t_vars *)malloc(sizeof(t_vars));
	g_vars->env = set_env(envp);
	while (1)
	{
		minishell = (t_minishell *)malloc(sizeof(t_minishell));
		if (initialize_minishell(minishell))
			return (printf("Failed to run minishell\n"));
		if (minishell->scanner->command == NULL)
			return (exit_shell());
		if (check_spaces(minishell->scanner->command))
			leaks_one(minishell);
		else
			__parse_and_execute__(minishell);
	}
	return (0);
}
