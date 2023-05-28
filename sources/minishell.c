/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/28 18:27:47 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_parser	*parser;
	t_prompt	*prompt;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = NULL;
	env = init_env(env, envp);
	while (1)
	{
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		parser = (t_parser *)malloc(sizeof(t_parser));
		parser->cmd = prompt_string(prompt);
		if (ft_strlen(parser->cmd))
			final_tokens(parser, env);
		if (ft_strlen(parser->cmd))
			add_history(parser->cmd);
		free_pointers(prompt, parser);
	}
	return (0);
}
