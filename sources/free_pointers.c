/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:21:05 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/26 23:46:53 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

void	free_pointers(t_lexer *lexer, t_prompt *prompt, t_parser *parser)
{
	free(lexer->cmd);
	free(lexer);
	free(parser);
	free(prompt->line);
	free(prompt);
}
