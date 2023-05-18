/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 03:02:41 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/18 19:44:35 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	init_search(t_parser *parser)
{
	struct dirent	*dir_entry;
	DIR				*dir;

	parser->req = ft_split(parser->tokens[parser->i], '*');
	parser->matched = (void *)0;
	dir = opendir(".");
	if (!dir)
		printf("No such file or directory");
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		parser->p_match = ft_strdup(dir_entry->d_name);
		search_for_match(parser);
		dir_entry = readdir(dir);
	}
	if (parser->matched)
		match_found(parser);
	else
		match_not_found(parser);
	free_array(parser->req);
	closedir(dir);
}

void	wildcards_expander(t_parser *parser)
{
	parser->j = -1;
	parser->wc_is_last = 0;
	if (!should_expand(parser->tokens[parser->i]))
	{
		while (parser->tokens[parser->i][++parser->j])
		{
			if (parser->tokens[parser->i][parser->j] == '*')
			{
				if (!parser->tokens[parser->i][parser->j + 1])
					parser->wc_is_last = 1;
				init_search(parser);
				break ;
			}
		}
	}
}
