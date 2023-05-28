/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:24:47 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/28 18:27:29 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	final_tokens(t_parser *parser, t_env *env)
{
	tokenizer(parser);
	if (parser->error == 1)
		ft_putendl_fd("[!] Error: There is an unclosed quote", 1);
	else if (parser->error == 2)
		ft_putendl_fd("[!] Error : parse error near to a symbol", 1);
	else
	{
		variables_expander(parser, env);
		quotes_removal(parser);
		tokens_traversal(parser->tokens);
		free_array(parser->tokens);
	}
}
