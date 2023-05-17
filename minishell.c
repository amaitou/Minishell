/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/17 03:32:29 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(void)
{
	t_lexer		*lexer;
	t_prompt	*prompt;
	int			tokenizer_value;

	while (1)
	{
		lexer = (t_lexer *)malloc(sizeof(t_lexer));
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		lexer->cmd = prompt_string(prompt);
		if (ft_strlen(lexer->cmd))
		{
			add_history(lexer->cmd);
			tokenizer_value = tokenizer(lexer);
			if (tokenizer_value == 1)
				ft_putendl_fd("[!] Error: There is an unclosed quote", 1);
			else if (tokenizer_value == 2)
				ft_putendl_fd("[!] Error : parse error near to a symbol", 1);
			else
			{
				tokens_traversal(lexer->tokens);
				free_array(lexer->tokens);
			}
			free(lexer->cmd);
		}
		else
			free(lexer->cmd);
		free(lexer);
		free(prompt->line);
		free(prompt);
	}
	return (0);
}