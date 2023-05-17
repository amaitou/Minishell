/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 03:02:41 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/17 04:30:48 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	init_search(t_lexer *lexer)
{
	struct dirent	*dir_entry;
	DIR				*dir;

	lexer->req = ft_split(lexer->tokens[lexer->i], '*');
	lexer->matched = NULL;
	dir = opendir(".");
	if (!dir)
		printf("No such file or directory");
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		lexer->p_match = ft_strdup(dir_entry->d_name);
		search_for_match(lexer);
		dir_entry = readdir(dir);
	}
	if (lexer->matched)
		match_found(lexer);
	else
		match_not_found(lexer);
	free_array(lexer->req);
	closedir(dir);
}

void	wildcards_expander(t_lexer *lexer)
{
	lexer->j = -1;
	lexer->wc_is_last = 0;
	if (!should_expand(lexer->tokens[lexer->i]))
	{
		while (lexer->tokens[lexer->i][++lexer->j])
		{
			if (lexer->tokens[lexer->i][lexer->j] == '*')
			{
				if (!lexer->tokens[lexer->i][lexer->j + 1])
					lexer->wc_is_last = 1;
				init_search(lexer);
				break ;
			}
		}
	}
}
