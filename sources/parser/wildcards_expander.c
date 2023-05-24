/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 03:02:41 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/24 16:20:25 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	parser->first = 0;
	parser->last = 0;
	parser->wc_present = 0;
	if (!should_expand(parser->tokens[parser->i]))
	{
		while (parser->tokens[parser->i][++parser->j])
		{
			if (parser->tokens[parser->i][parser->j] == '*')
			{
				if (parser->j && !parser->first && !parser->wc_present)
					parser->first = 1;
				parser->wc_present = 1;
			}
			else if (parser->wc_present && !parser->last)
				if (!ft_strchr(&parser->tokens[parser->i][parser->j + 1],
					'*'))
					parser->last = 1;
		}
		if (parser->wc_present)
			init_search(parser);
	}
}
