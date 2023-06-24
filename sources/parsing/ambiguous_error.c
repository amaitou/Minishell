/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:45:07 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 01:49:06 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ambigous_helper_2(t_dlist *lexer, t_errors *error, char **names)
{
	if (lexer->next->value && check_spaces(lexer->next->value))
	{
		error->error_type = error_of_ambiguous;
		free_tokens(names);
		return (1);
	}
	if (!lexer->next->value)
	{
		error->error_type = error_of_ambiguous;
		free_tokens(names);
		return (1);
	}
	return (0);
}

int	ambiguous_error_helper(t_dlist *lexer, t_errors *error)
{
	char	**names;

	names = ft_split(lexer->next->value, ' ');
	if (names)
	{
		if (count_number_of_names(names, error))
			return (1);
	}
	if ((lexer->next->value && lexer->next->value[0] == '\0'))
	{
		error->error_type = error_of_space_redirection;
		free_tokens(names);
		return (1);
	}
	if (ambigous_helper_2(lexer, error, names))
		return (1);
	return (0);
}

void	check_ambiguous(t_dlist *lexer, t_errors *error)
{
	int		i;

	while (lexer)
	{
		i = 0;
		if (lexer->type == __RED_APP
			||lexer->type == __RED_OUT || lexer->type == __RED_IN)
		{
			if (ambiguous_error_helper(lexer, error))
				return ;
		}
		lexer = lexer->next;
	}
	error->error_type = no_error;
}
