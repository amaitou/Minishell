/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 03:02:41 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/15 04:55:44 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
		l->p_matches = ft_strdup(dir_entry->d_name);
		i = 0;
		j = 0;
		while (ft_strnstr(l->p_matches + j, l->req[i], ft_strlen(l->p_matches)))
		{
			i++;
			if (!l->req[i])
			{
				l->matched = string_join(l->matched, l->p_matches);
				l->matched = string_join(l->matched, ft_strdup(" "));
				break ;
			}
			j = ft_strlen(l->req[i]);
		}
		if (l->req[i])
			free (l->p_matches);
		dir_entry = readdir(dir);
	}
	free(l->tokens[l->i]);
	l->tokens[l->i] = ft_strdup("");
	if (l->matched)
	{
		free(l->tokens[l->i]);
		l->tokens[l->i] = ft_strdup(l->matched);
		free (l->matched);
	}
	closedir(dir);
}

void	expand_wildcards(t_lexer *l)
{
	l->i = -1;
	while (l->tokens[++l->i])
	{
		l->j = -1;
		l->param_exp = 0;
		while (l->tokens[l->i][++l->j])
		{
			if (l->tokens[l->i][l->j] == '$')
				l->param_exp = 1;
			else if (l->tokens[l->i][l->j] == '*' && !l->param_exp)
			{
				search_for_match(l);
				break ;
			}
		}
	}
}
