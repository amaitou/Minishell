/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcards_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:21:44 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 13:37:55 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clean_resources(char **resource)
{
	int	i;

	i = -1;
	while (resource[++i])
		free(resource[i]);
	free(resource);
}

static void	init_search(t_dlist *list)
{
	struct dirent	*dir_entry;
	DIR				*dir;

	list->req = ft_split(list->value, '*');
	list->matched = NULL;
	dir = opendir(".");
	if (!dir)
		printf("No such file or directory");
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		list->p_match = ft_strdup(dir_entry->d_name);
		search_for_match(list);
		dir_entry = readdir(dir);
	}
	if (list->matched)
		match_found(list);
	clean_resources(list->req);
	closedir(dir);
}

void	wildcards_expander(t_dlist *list)
{
	list->i = -1;
	list->first = 0;
	list->last = 0;
	list->wc_present = 0;
	if (!should_expand(list->value))
	{
		while (list->value[++list->i])
		{
			if (list->value[list->i] == '*')
			{
				if (list->i && !list->first && !list->wc_present)
					list->first = 1;
				list->wc_present = 1;
			}
			else if (list->wc_present && !list->last)
				if (!ft_strchr(&list->value[list->i + 1], '*'))
					list->last = 1;
		}
		if (list->wc_present)
			init_search(list);
	}
}
