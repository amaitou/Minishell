/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:28:02 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/21 15:06:26 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_len(t_parser *parser, int i)
{
	if (parser->wc_is_last && parser->req[0])
		return (ft_strlen(parser->req[i]));
	else
		return (ft_strlen(parser->p_match));
}

int	should_expand(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '$' && string[i])
		i++;
	return (ft_strlen(string) - i);
}

void	match_found(t_parser *parser)
{
	free(parser->tokens[parser->i]);
	parser->tokens[parser->i] = ft_strdup(parser->matched);
	free (parser->matched);
}

void	match_not_found(t_parser *parser)
{
	printf("no matches found: %s\n", parser->tokens[parser->i]);
	free(parser->tokens[parser->i]);
	parser->tokens[parser->i] = ft_strdup("");
}

void	search_for_match(t_parser *parser)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (parser->p_match[0] == '.')
		return ;
	while (parser->req[++i] && ft_strnstr(parser->p_match + j,
			parser->req[i], find_len(parser, i)))
		j = ft_strlen(parser->req[i]);
	if (!parser->req[i])
	{
		parser->matched = string_join(parser->matched, parser->p_match);
		parser->matched = string_join(parser->matched, ft_strdup(" "));
	}
	else
		free (parser->p_match);
}
