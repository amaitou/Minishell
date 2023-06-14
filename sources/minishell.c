/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/14 01:57:31 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **set_env(char **envp)
{
	char **env;
	int	size;
	int	i;

	i = -1;
	size = 0;
	while (envp[++i]) // calculating size of envp
		size++;
	i = -1;
	env = (char **)malloc((size + 1) * sizeof(char *));
	while (envp[++i]) // copying contents of envp to our own env
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_scanner	*scanner;
	t_prompt	*prompt;
	t_dlist		*head;
	t_errors	*error;
	int			return_value;
	char		**env;

	(void)argc;
	(void)argv;
	env = set_env(envp);
	while (1)
	{
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		scanner = (t_scanner *)malloc(sizeof(t_scanner));
		error = (t_errors *)malloc(sizeof(t_errors));
		scanner->command = prompt_string(prompt);
		head = NULL;
		return_value = __check__(scanner, prompt, error);
		if (return_value == 1)
			exit(1);
		if (!(return_value == 2))
			__parse__(scanner, head, error, prompt);
	}
	return (0);
}
