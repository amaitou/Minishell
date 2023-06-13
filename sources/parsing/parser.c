/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:00:09 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/13 22:56:50 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	__parser__(t_parser **parser, t_dlist *head)
{
	t_parser		*node;
	t_list			*file;
	char			*args;

	while (head)
	{
		node = __create_node();
		file = NULL;
		args = NULL;
		while (head && head->type != __PIPE)
		{
			if ((head->type == __WORD && !head->prev)
				|| (head->type == __WORD && (head->prev->type == __WORD
						|| head->prev->type == __PIPE)))
			{
				args = string_join(args, head->value);
				args = string_join(args, ft_strdup("\n"));
			}
			else if ((head->type == __RED_APP || head->type == __RED_IN
					|| head->type == __HEREDOC || head->type == __RED_OUT))
			{
				file = ft_lstnew();
			}
			head = head->next;
		}
		node->args = ft_split(args, '\n');
		node->file[i].name = NULL;
		__append_node(parser, node);
		if (head)
			head = head->next;
	}
}
