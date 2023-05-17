/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:35 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/17 22:22:26 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./minishell.h"

typedef struct s_lexer
{
	int		i;
	int		j;
	int		param_exp;
	int		wc_is_last;
	char	*line;
	char	quote;
	char	**tokens;
	char	**req;
	char	*p_match;
	char	*matched;
	char	*cmd;
}	t_lexer;

typedef enum e_cntrl_op
{
	RED_IN,
	RED_OUT,
	RED_OUT_APP,
	RED_IN_DEL,
	PIPE,
	COMMAND
}	t_cntrl_op;

typedef struct s_info
{
	char			*full_cmd;
	t_cntrl_op		op;
	struct s_info	*next;
}	t_info;

int		quotes(t_lexer *lexer, char *s);
int		operators(t_lexer *lexer, char *s);
int		scanner(char *s, t_lexer *lexer);
int		tokenizer(t_lexer *lexer, t_env *env);
void	variables_expander(t_lexer *lexer, t_env *env);
void	tokens_traversal(char **tokenizer);
void	free_struct(t_lexer *lexer);
void	wildcards_expander(t_lexer *lexer);
void	free_array(char **arr);
void	free_line(char *s);

/**
 * @brief Declarations for wildcards expander utils funcs
 * 
 */

int		find_len(t_lexer *lexer, int i);
char	*find_format(t_lexer *lexer, int i);
int		should_expand(char *string);
void	match_found(t_lexer *lexer);
void	match_not_found(t_lexer *lexer);
void	search_for_match(t_lexer *lexer);

#endif
