/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:28:02 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/17 04:30:32 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	find_len(t_lexer *lexer, int i)
{
	if (lexer->wc_is_last && lexer->req[0])
		return (ft_strlen(lexer->req[i]));
	else
		return (ft_strlen(lexer->p_match));
}

int	should_expand(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '$' && string[i])
		i++;
	return (ft_strlen(string) - i);
}

void	match_found(t_lexer *lexer)
{
	free(lexer->tokens[lexer->i]);
	lexer->tokens[lexer->i] = ft_strdup(lexer->matched);
	free (lexer->matched);
}

void	match_not_found(t_lexer *lexer)
{
	printf("no matches found: %s\n", lexer->tokens[lexer->i]);
	free(lexer->tokens[lexer->i]);
	lexer->tokens[lexer->i] = ft_strdup("");
}

void	search_for_match(t_lexer *lexer)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (lexer->req[++i] && ft_strnstr(lexer->p_match + j,
			lexer->req[i], find_len(lexer, i)))
		j = ft_strlen(lexer->req[i]);
	if (!lexer->req[i])
	{
		lexer->matched = string_join(lexer->matched, lexer->p_match);
		lexer->matched = string_join(lexer->matched, ft_strdup(" "));
	}
	else
		free (lexer->p_match);
}
