/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/17 18:23:05 by bbouagou         ###   ########.fr       */
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
	while (envp[++i])
		size++;
	i = -1;
	env = (char **)malloc((size + 1) * sizeof(char *));
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_scanner	*scanner;
	t_prompt	*prompt;
	t_dlist		*head;
	t_errors	*error;
	t_vars		*vars;
	int			return_value;

	(void)argc;
	(void)argv;
	vars = (t_vars *)malloc(sizeof(t_vars));
	vars->env = set_env(envp);
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
			__parse__(scanner, head, error, prompt, vars);
	}
	return (0);
}
