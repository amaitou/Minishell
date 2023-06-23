/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:53:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/23 15:35:02 by amait-ou         ###   ########.fr       */
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

int	ambiguous_error_helper(t_dlist *lexer, t_errors *error)
{
	char	**names;

	names = ft_split(lexer->next->value, ' ');
	if (names)
	{
		if (count_number_of_names(names, error))
			return (1);
	}
	if (lexer->next->value[0] == '\0')
	{
		error->error_type = error_of_ambiguous;
		free_tokens(names);
		return (1);
	}
	return (0);
}

void	check_ambiguous(t_dlist *lexer, t_errors *error)
{
	int		i;

	while (lexer)
	{
		i = 0;
		if (lexer->type == __RED_APP
			||lexer->type == __RED_OUT || lexer->type == __RED_IN)
		{
			if (ambiguous_error_helper(lexer, error))
				return ;
		}
		lexer = lexer->next;
	}
	error->error_type = no_error;
}

int	error_ambiguous(t_minishell *minishell)
{
	check_ambiguous(minishell->lexer, minishell->error);
	if (minishell->error->error_type == error_of_ambiguous)
	{
		display_error(minishell->error);
		add_history(minishell->scanner->command);
		return (1);
	}
	else
		return (0);
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
		params_expander(minishell->lexer, g_vars->env);
		quotes_removal(minishell->lexer);
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
