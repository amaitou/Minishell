/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/14 22:07:38 by amait-ou         ###   ########.fr       */
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
		if (!ft_strlen(lexer->cmd))
			lexer->cmd = prompt_string();
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
