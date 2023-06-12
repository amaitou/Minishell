/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:00:09 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/12 22:03:29 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	__parser__(t_parser *parser, t_dlist *head)
{
	t_parser		*node;
	char			*args;
	int				i;

	(void)parser;
	while (head)
	{
		i = 0;
		node = __create_node();
		args = NULL;
		while (head && head->type != __PIPE)
		{
			if ((head->type == __WORD && !head->prev)
				|| (head->type == __WORD && (head->prev->type == __WORD
						|| head->prev->type == __PIPE)))
				printf("%s\n", head->value);
			head = head->next;
		}
		if (head)
			head = head->next;
	}
}
