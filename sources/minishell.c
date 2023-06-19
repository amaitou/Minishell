/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/19 14:42:54 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**set_env(char **envp)
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

static void	signal_handler(int signal, siginfo_t *siginfo, void *context)
{
	int	status;

	if (signal == SIGINT)
	{
		wait(&status);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (WIFSIGNALED(status) == FALSE)
			rl_redisplay();
		else
			g_vars->exit_status = 130;
	}
}

static int	exit_shell(void)
{
	printf("exit\n");
	return (g_vars->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_scanner			*scanner;
	t_prompt			*prompt;
	t_dlist				*head;
	t_errors			*error;
	struct sigaction	sigact;
	int					return_value;

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
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		scanner = (t_scanner *)malloc(sizeof(t_scanner));
		error = (t_errors *)malloc(sizeof(t_errors));
		scanner->command = prompt_string(prompt);
		if (scanner->command == NULL)
			return (exit_shell());
		head = NULL;
		return_value = __check__(scanner, prompt, error);
		if (return_value == 1)
			exit(1);
		if (!(return_value == 2))
			__parse__(scanner, head, error, prompt);
	}
	return (0);
}
