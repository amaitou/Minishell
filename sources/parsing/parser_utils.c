/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:10:50 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 00:38:54 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redirection(t_dlist *lexer)
{
	if (lexer->type == __RED_APP || lexer->type == __RED_IN
		|| lexer->type == __HEREDOC || lexer->type == __RED_OUT)
		return (1);
	return (0);
}

int	check_args(t_dlist *lexer)
{
	if ((lexer->type == __WORD && !lexer->prev)
		|| (lexer->type == __WORD && (lexer->prev->type == __WORD
				|| lexer->prev->type == __PIPE)))
		return (1);
	return (0);
}

void	assign_file(t_dlist *lexer, t_list *file, t_list **node)
{
	file->name = ft_strdup(lexer->next->value);
	if (lexer->type == __RED_IN)
		file->type = IN;
	else if (lexer->type == __RED_OUT)
		file->type = OUT;
	else if (lexer->type == __RED_APP)
		file->type = APPEND;
	else if (lexer->type == __HEREDOC)
		file->type = HEREDOC;
	else
		file->type = NONE;
	ft_lstadd_back(node, file);
}

void	assign_args(t_dlist *lexer, char **args)
{
	if (lexer->value)
	{
		*args = string_join(*args, ft_strdup(lexer->value));
		*args = string_join(*args, ft_strdup("\n"));
	}
}
