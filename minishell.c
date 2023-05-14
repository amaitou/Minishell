/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/14 19:09:01 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(void)
{
	t_lexer	*lexer;

	while (1)
	{
		lexer = (t_lexer *)malloc(sizeof(t_lexer));
		lexer->cmd = prompt_string();
		if (!lexer->cmd)
			printf("NONE\n");
		else
		{
			tokenizer(lexer);
			tokens_traversal(lexer->tokens);
			add_history(lexer->cmd);
			free_struct(lexer);
		}
	}
	return (0);
}
