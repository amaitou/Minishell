/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/18 21:49:44 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_prompt	*prompt;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = NULL;
	env = initialize_environnement(env, envp);
	while (1)
	{
		lexer = (t_lexer *)malloc(sizeof(t_lexer));
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		parser = (t_parser *)malloc(sizeof(t_parser));

		lexer->cmd = prompt_string(prompt);
		if (ft_strlen(lexer->cmd))
		{
			parser->tokens = tokenizer(lexer);
			if (lexer->error == 1)
				ft_putendl_fd("[!] Error: There is an unclosed quote", 1);
			else if (lexer->error == 2)
				ft_putendl_fd("[!] Error : parse error near to a symbol", 1);
			else
			{
				variables_expander(parser, env);
				tokens_traversal(lexer->tokens);
				free_array(lexer->tokens);
			}
		}
		if (ft_strlen(lexer->cmd))
			add_history(lexer->cmd);
		free_pointers(lexer, prompt, parser);
	}
	return (0);
}
