/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:56:54 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/18 20:01:29 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

typedef struct s_parser
{
	int		param_exp;
	char	**tokens;
	char	**req;
	char	*p_match;
	char	*matched;
	int		wc_is_last;
	int		i;
	int		j;
}	t_parser;

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

void	variables_expander(t_parser *parser, t_env *env);
void	wildcards_expander(t_parser *parser);

/**
 * @brief Declarations for wildcards expander utils funcs
 * 
 */

int		find_len(t_parser *parser, int i);
char	*find_format(t_parser *parser, int i);
int		should_expand(char *string);
void	match_found(t_parser *parser);
void	match_not_found(t_parser *parser);
void	search_for_match(t_parser *parser);

#endif