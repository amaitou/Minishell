/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 03:02:41 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/16 15:16:43 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	find_len(t_lexer *lexer, int i)
{
	if (lexer->wc_is_last)
		return (ft_strlen(lexer->req[i]));
	else
		return (ft_strlen(lexer->p_match));
}

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
		while (ft_strnstr(lexer->p_match + j, lexer->req[i], find_len(lexer, i)))
		{
			i++;
			if (!lexer->req[i])
			{
				lexer->matched = string_join(lexer->matched, lexer->p_match);
				lexer->matched = string_join(lexer->matched, ft_strdup(" "));
				break ;
			}
			j = ft_strlen(lexer->req[i]);
		}
		if (lexer->req[i])
			free (lexer->p_match);
		dir_entry = readdir(dir);
	}
	if (lexer->matched)
	{
		free(lexer->tokens[lexer->i]);
		lexer->tokens[lexer->i] = ft_strdup(lexer->matched);
		free (lexer->matched);
	}
	else
	{
		printf("no matches found: %s\n", lexer->tokens[lexer->i]);
		free(lexer->tokens[lexer->i]);
		lexer->tokens[lexer->i] = ft_strdup("");
	}
	closedir(dir);
}

static int	should_expand(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '$' && string[i])
		i++;
	return (ft_strlen(string) - i);
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
