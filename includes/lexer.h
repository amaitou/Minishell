/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:36 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/11 04:47:03 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./minishell.h"

/**
 * @brief An enum which has all control operators for a command.
 */

typedef enum e_cntrl_op
{
	RED_IN,
	RED_OUT,
	RED_OUT_APP,
	RED_IN_DEL,
	PIPE
}	t_cntrl_op;

/**
 * @brief A linked list containing commands and their arguments.
 */

typedef struct s_info
{
	char		*full_cmd;
	t_cntrl_op	op;
}	t_info;

char	*handle_quotes(char *p, int *q, char c);
char	*split_command(char *s);
char	**create_tokens(char *s);
void	tokens_traversal(char **t);

#endif