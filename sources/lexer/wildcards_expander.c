/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 03:02:41 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/17 03:48:07 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	search_for_match(t_lexer *lexer)
{
	struct dirent	*dir_entry;
	DIR				*dir;
	int				i;
	int				j;

	lexer->req = ft_split(lexer->tokens[lexer->i], '*');
	lexer->matched = NULL;
	dir = opendir(".");
	if (!dir)
		printf("No such file or directory");
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		lexer->p_match = ft_strdup(dir_entry->d_name);
		i = 0;
		j = 0;
		while (ft_strnstr(lexer->p_match + j,
				find_format(lexer, i), find_len(lexer, i)))
		{
			i++;
			if (!lexer->req[i])
			{
				lexer->matched = string_join(lexer->matched, lexer->p_match);
				lexer->matched = string_join(lexer->matched, ft_strdup(" "));
				break ;
			}
			if (lexer->req[i])
				j = ft_strlen(lexer->req[i]);
		}
		if (lexer->req[i])
			free (lexer->p_match);
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
				search_for_match(lexer);
				break ;
			}
		}
	}
}
