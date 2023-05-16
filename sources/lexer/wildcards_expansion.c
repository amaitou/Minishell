/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 03:02:41 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/16 01:17:54 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	find_len(t_lexer *l, int i)
{
	if (l->wc_is_last)
		return (ft_strlen(l->req[i]));
	else
		return (ft_strlen(l->p_match));
}

static void	search_for_match(t_lexer *l)
{
	struct dirent	*dir_entry;
	DIR				*dir;
	int				i;
	int				j;

	l->req = ft_split(l->tokens[l->i], '*');
	l->matched = NULL;
	dir = opendir(".");
	if (!dir)
		printf("No such file or directory");
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		l->p_match = ft_strdup(dir_entry->d_name);
		i = 0;
		j = 0;
		while (ft_strnstr(l->p_match + j, l->req[i], find_len(l, i)))
		{
			i++;
			if (!l->req[i])
			{
				l->matched = string_join(l->matched, l->p_match);
				l->matched = string_join(l->matched, ft_strdup(" "));
				break ;
			}
			j = ft_strlen(l->req[i]);
		}
		if (l->req[i])
			free (l->p_match);
		dir_entry = readdir(dir);
	}
	if (l->matched)
	{
		free(l->tokens[l->i]);
		l->tokens[l->i] = ft_strdup(l->matched);
		free (l->matched);
	}
	else
	{
		printf("no matches found: %s\n", l->tokens[l->i]);
		free(l->tokens[l->i]);
		l->tokens[l->i] = ft_strdup("");
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

void	expand_wildcards(t_lexer *l)
{
	l->j = -1;
	l->wc_is_last = 0;
	if (!should_expand(l->tokens[l->i]))
	{
		while (l->tokens[l->i][++l->j])
		{
			if (l->tokens[l->i][l->j] == '*')
			{
				if (!l->tokens[l->i][l->j + 1])
					l->wc_is_last = 1;
				search_for_match(l);
				break ;
			}
		}
	}
}
