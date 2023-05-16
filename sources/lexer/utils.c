/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:51:54 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/16 15:37:03 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	tokens_traversal(char **tokenizer)
{
	int	i;

	i = -1;
	while (tokenizer[++i])
		printf(" [.] %s\n", tokenizer[i]);
}

void	free_struct(t_lexer *lexer)
{
	int	i;

	i = -1;
	free (lexer->cmd);
	while (lexer->tokens[++i])
		free(lexer->tokens[i]);
	free(lexer->tokens);
	free(lexer);
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}