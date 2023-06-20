/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:53:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/20 18:57:11 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	__parse_and_execute__(t_minishell *minishell)
{
	__scanner__(minishell);
	__lexer__(minishell);
	__error__(minishell);
	if (minishell->error->error_type != no_error)
	{
		display_error(minishell->error);
		add_history(minishell->scanner->command);
		leaks_one(minishell);
	}
	else
	{
		quotes_removal(minishell->lexer);
		__parser__(&minishell->parser, minishell->lexer);
		add_history(minishell->scanner->command);
		leaks_two(minishell);
	}
}
