/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:57:38 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/03 19:27:25 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenizer(t_dlist *head, char *token)
{
	if (token[0] == '\"' || token[0] == '\"')
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

void	__lexer(t_dlist *head, t_scanner *scanner)
{
	printf("IN");
	t_dlist	*temp;

	temp = head;
	scanner->i = -1;
	while (scanner->tokens[++scanner->i])
	{
		tokenizer(temp, scanner->tokens[scanner->i]);
		printf("value -> %s\n", temp->value);
		temp = temp->next;
	}
}