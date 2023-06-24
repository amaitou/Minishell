/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:53:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 01:14:20 by bbouagou         ###   ########.fr       */
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
	if ((lexer->next->value && lexer->next->value[0] == '\0'))
	{
		error->error_type = error_of_space_redirection;
		free_tokens(names);
		return (1);
	}
	if (lexer->next->value && check_spaces(lexer->next->value))
	{
		error->error_type = error_of_ambiguous;
		free_tokens(names);
		return (1);
	}
	if (!lexer->next->value)
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

void	split_expanded_tokens(t_dlist *list)
{
	char	**tmp;
	t_dlist	*tmp_n;
	int		i;

	tmp_n = NULL;
	while (list)
	{
		if (!ft_strchr(list->value, '\'') && !ft_strchr(list->value, '\"')
			&& ft_strchr(list->value, ' '))
		{
			tmp = ft_split(list->value, ' ');
			if (tmp && tmp[0])
			{
				i = 0;
				free(list->value);
				list->value = ft_strdup(tmp[i]);
				++i;
				while (list && tmp[i])
				{
					tmp_n = create_node();
					tmp_n->type = __WORD;
					tmp_n->value = ft_strdup(tmp[i]);
					tmp_n->prev = list;
					tmp_n->next = list->next;
					if (list->next)
						list->next->prev = tmp_n;
					list->next = tmp_n;
					list = list->next;
					++i;
				}
			}
			else
			{
				list->prev->next = list->next;
				free(list->value);
				free(list);
			}
			if (tmp)
				clean(tmp);
		}
		list = list->next;
	}
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
		split_expanded_tokens(minishell->lexer);
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
