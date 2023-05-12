/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:36 by amait-ou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/12 17:28:16 by amait-ou         ###   ########.fr       */
=======
/*   Updated: 2023/05/11 04:47:03 by bbouagou         ###   ########.fr       */
>>>>>>> 41c761d0d448382e8165c2225a6c1b70b3ac6205
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./minishell.h"

<<<<<<< HEAD
typedef struct s_lexer
{
	int		i;
	int		j;
	char	*line;
	char	c;
}	t_lexer;

void	quotes(t_lexer *lexer, char *s);
void	operators(t_lexer *lexer, char *s);
char 	*scanner(char *s);
char	**tokenizer(char *s);
=======
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
>>>>>>> 41c761d0d448382e8165c2225a6c1b70b3ac6205
void	tokens_traversal(char **t);

#endif