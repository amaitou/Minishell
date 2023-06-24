/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_leaks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:45:49 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 08:25:53 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	leaks_one(t_minishell *minishell)
{
	free(minishell->prompt->line);
	free(minishell->prompt);
	free(minishell->scanner->command);
	free(minishell->scanner);
	clear_lexer(&minishell->lexer, del);
	free(minishell->error);
	free(minishell);
}

void	leaks_two(t_minishell *minishell)
{
	free(minishell->prompt->line);
	free(minishell->prompt);
	free(minishell->scanner->command);
	free(minishell->scanner);
	free(minishell->error);
	clear_lexer(&minishell->lexer, del);
	clear_parser(&minishell->parser, del);
	free(minishell);
}
