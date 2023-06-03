/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 01:28:16 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/03 02:33:05 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_quotes(t_dlist *head, t_scanner *scanner)
{
	t_dlist *node;

	scanner->j = scanner->i++;
	while (scanner->command[scanner->i] != scanner->t_quote
		&& scanner->command[scanner->i])
		scanner->i++;
	if (scanner->command[scanner->i])
	{
		node = create_node();
		node->value = ft_substr(scanner->command, scanner->j,
			scanner->i - scanner->j + 1);
		node->type = __NONE;
		if (scanner->t_quote == '\"')
			node->state = __d_quotes;
		else
			node->state = __s_quotes;
		append_node(head, node);
	}
	else
		return (1);
	return (0);
}

int handle_operators(t_dlist *head, t_scanner *scanner)
{
	t_dlist *node;

	if (!ft_memcmp(scanner->command + scanner->i, ">>", 2)
		|| !ft_memcmp(scanner->command + scanner->i, "<<", 2))
	{
		node->value = ft_substr(scanner->command, scanner->i, 2);
		if (!ft_memcmp(scanner->command + scanner->i, ">>", 2))
			node->type = __RED_APP;
		else
			node->type = __HEREDOC;
		scanner->i++;
	}
	else
	{
		node->value = ft_substr(scanner->command, scanner->i, 1);
		if (scanner->command[scanner->i] == '<')
			node->type = __RED_IN;
		else
			node->type = __RED_OUT;
	}
	node->state = __none;
	return (0);
}

int command_scanner(t_dlist *head, t_scanner *scanner)
{
	t_dlist *node;

	while (scanner->command[scanner->i])
	{
		if (scanner->command[scanner->i] == '\"'
			|| scanner->command[scanner->i] == '\'')
		{
			scanner->t_quote = scanner->command[scanner->i];
			if (handle_quotes(head, scanner))
				return (1);
		}
		else if (ft_strchr("<>|&", scanner->command[scanner->i]))
		{
			if (handle_operators(head, scanner))
				return (2);
		}
		else if (ft_strchr(" \t\n\v\f\r", scanner->command[scanner->i]))
			++scanner->i;
		else
		{
			node->value = ft_substr(scanner->command, scanner->i, 1);
			node->type = __NONE;
			node->state = __none;
		}
		scanner->i++;
	}
	return (0);
}

void tokenizer(t_dlist *head, t_scanner *scanner)
{
	scanner->i = 0;
	scanner->command = NULL;
	command_scanner(head, scanner);
}
