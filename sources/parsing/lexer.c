/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:57:38 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/07 18:15:55 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenizer(t_dlist **head, char *token)
{
	if (token[0] == '\'' || token[0] == '\"')
	{
		if (token[0] == '\'')
			append_node(head, node_quotes(token, '\''));
		else
			append_node(head, node_quotes(token, '\"'));
	}
	else if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		append_node(head, node_redirection(token));
	else if (!ft_strcmp(token, "|"))
		append_node(head, node_pipeline(token));
	else
		append_node(head, node_word(token));
}

void	quotes_removal(t_dlist *head)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (head)
	{
		if (head->state == __s_quotes)
			remove_quotes(head, '\'');
		else if (head->state == __d_quotes)
			remove_quotes(head, '\"');
		head = head->next;
	}
}

void	__lexer__(t_dlist **head, t_scanner *scanner)
{
	scanner->i = 0;
	while (scanner->tokens[scanner->i])
	{
		tokenizer(head, scanner->tokens[scanner->i]);
		++scanner->i;
	}
}
