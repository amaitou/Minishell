/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:22:50 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/04 01:18:37 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist *node_quotes(char *token, char quote)
{
	int	len;
	int	i;
	t_dlist	*node;
	char	*temp;

	len = ft_strlen(token);
	i = 0;
	node = create_node();
	if (quote == '\'')
		node->state = __s_quotes;
	else
		node->state = __d_quotes;
	if (token[i] == quote && token[len - 1] == quote)
		node->value = ft_strtrim(token, quote);
	else
	{
		while (token[i])
		{
			if (!(token[i] == quote))
				temp = string_join(temp, ft_substr(temp, i, 1));
			++i;
		}
		node->value = temp;
	}
	node->type = __NONE;
	return (node);
}

t_dlist	*node_redirection(char *token)
{
	t_dlist	*node;
	
	node = create_node();
	node->value = token;
	node->state = __none;
	if (ft_strcmp(token, ">"))
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
	t_dlist *node;

	node = create_node();
	node->value = token;
	node->state = __none;
	node->type = __PIPE;
	return (node);
}

t_dlist *node_word(char *token)
{
	t_dlist *node;

	node = create_node();
	node->value = token;
	node->state = __none;
	node->type = __NONE;
	return (node);
}