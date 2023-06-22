/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:01:04 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/22 18:05:11 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	initialize_minishell(t_minishell *minishell)
{
	minishell->prompt = (t_prompt *)malloc(sizeof(t_prompt));
	if (!minishell->prompt)
		return (1);
	minishell->scanner = (t_scanner *)malloc(sizeof(t_scanner));
	if (!minishell->scanner)
		return (2);
	minishell->error = (t_errors *)malloc(sizeof(t_errors));
	if (!minishell->error)
		return (3);
	minishell->scanner->command = prompt_string(minishell->prompt);
	minishell->parser = NULL;
	minishell->lexer = NULL;
	return (0);
}

int	check_spaces(char *s)
{
	while (*s && (*s == '\t' || *s == ' '))
		++s;
	if (*s)
		return (0);
	return (1);
}

char	**set_env(char **envp)
{
	char	**env;
	int		size;
	int		i;

	i = -1;
	size = 0;
	while (envp && envp[++i])
		size++;
	i = 0;
	env = (char **)malloc((size + 1) * sizeof(char *));
	while (envp && envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	signal_handler(int signal, siginfo_t *siginfo, void *context)
{
	int	status;

	(void)context;
	(void)siginfo;
	if (signal == SIGINT)
	{
		wait(&status);
		printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		if (WIFSIGNALED(status) == FALSE)
			rl_redisplay();
		else
			g_vars->exit_status = WTERMSIG(status) + 128;
	}
}
