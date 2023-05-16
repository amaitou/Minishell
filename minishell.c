/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/16 15:12:09 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(void)
{
	t_lexer	*lexer;
	int		tokenizer_value;

	while (1)
	{
		lexer = (t_lexer *)malloc(sizeof(t_lexer));
		lexer->cmd = prompt_string();
		add_history(lexer->cmd);
		if (!ft_strlen(lexer->cmd))
			lexer->cmd = prompt_string();
		else
		{
			tokenizer_value = tokenizer(lexer);
			if (tokenizer_value == 1)
				ft_putendl_fd("[!] Error: There is an unclosed quotes", 1);
			else if (tokenizer_value == 2)
				ft_putendl_fd("[!] Error : parse error near to a symbol", 1);
			else
			{
				tokens_traversal(lexer->tokens);
				free_struct(lexer);
			}
		}
	}
	return (0);
}
