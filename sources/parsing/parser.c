/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:18:30 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/20 16:43:41 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_args(t_parser *node, char *args)
{
	if (node)
		node->args = ft_split(args, '\n');
	else
		node->args = NULL;
	free(args);
}

void	move_lexer(t_parser *node, t_dlist **lexer,
	t_parser **parser, char *args)
{
	split_args(node, args);
	if (*lexer)
	{
		node->type = __PIPE;
		(*lexer) = (*lexer)->next;
	}
	else
		node->type = __WORD;
	__append_node(parser, node);
}

void	__parser__(t_parser **parser, t_dlist *lexer)
{
	t_parser		*node;
	t_list			*file;
	char			*args;

	while (lexer)
	{
		node = __create_node();
		node->file = NULL;
		args = NULL;
		while (lexer && lexer->type != __PIPE)
		{
			file = ft_lstnew();
			if (check_redirection(lexer))
				assign_file(lexer, file, &node->file);
			else if (check_args(lexer))
			{
				if (lexer->value)
					assign_args(lexer, &args);
			}
			lexer = lexer->next;
		}
		move_lexer(node, &lexer, parser, args);
	}
}
