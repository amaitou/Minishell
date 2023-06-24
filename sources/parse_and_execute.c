/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:53:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 02:59:23 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_number_of_names(char **names, t_errors *error)
{
	int	i;

	i = 0;
	while (names[i])
		++i;
	if (i > 1)
	{
		error->error_type = error_of_ambiguous;
		free_tokens(names);
		return (1);
	}
	return (0);
}

int	error_ambiguous(t_minishell *minishell)
{
	check_ambiguous(minishell->lexer, minishell->error);
	if (minishell->error->error_type == error_of_ambiguous
		|| minishell->error->error_type == error_of_space_redirection)
	{
		display_error(minishell->error);
		add_history(minishell->scanner->command);
		return (1);
	}
	else
		return (0);
}

void	parse_and_execute_helper(t_minishell *minishell)
{
	params_expander(minishell->lexer, g_vars->env);
	split_expanded_tokens(minishell->lexer);
	quotes_removal(minishell->lexer);
}

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
		minishell->lexer->prev = minishell->lexer;
		parse_and_execute_helper(minishell);
		if (error_ambiguous(minishell))
			leaks_one(minishell);
		else
		{
			__parser__(&minishell->parser, minishell->lexer);
			minishell->parser->prev = minishell->parser;
			executor(minishell->parser);
			add_history(minishell->scanner->command);
			leaks_two(minishell);
		}
	}
}
