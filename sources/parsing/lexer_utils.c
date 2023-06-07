/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:22:50 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/07 18:14:52 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist	*node_quotes(char *token, char quote)
{
	t_dlist	*node;

	node = create_node();
	if (quote == '\'')
		node->state = __s_quotes;
	else
		node->state = __d_quotes;
	node->value = token;
	node->type = __WORD;
	return (node);
}

t_dlist	*node_redirection(char *token)
{
	t_dlist	*node;

	node = create_node();
	node->value = token;
	node->state = __without_quotes;
	if (!ft_strcmp(token, ">"))
		node->type = __RED_OUT;
	else if (!ft_strcmp(token, ">>"))
		node->type = __RED_APP;
	else if (!ft_strcmp(token, "<"))
		node->type = __RED_IN;
	else if (!ft_strcmp(token, "<<"))
		node->type = __HEREDOC;
	return (node);
}

t_dlist	*node_pipeline(char *token)
{
	t_dlist	*node;

	node = create_node();
	node->value = token;
	node->state = __without_quotes;
	node->type = __PIPE;
	return (node);
}

t_dlist	*node_word(char *token)
{
	t_dlist	*node;

	node = create_node();
	node->value = token;
	node->state = __without_quotes;
	node->type = __WORD;
	return (node);
}

void	remove_quotes(t_dlist *head, char quote)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (head->value[i])
	{
		if (!(head->value[i] == quote))
			temp = string_join(temp, ft_substr(head->value, i, 1));
		++i;
	}
	head->value = temp;
}
