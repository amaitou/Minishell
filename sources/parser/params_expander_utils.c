/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expander_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:52:37 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/26 15:57:12 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_index(char *token)
{
	int	i;

	i = 0;
	while (token[i] && !ft_strchr("$\'", token[i]))
		i++;
	return (--i);
}

int	is_valid(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

int	skip_quotes(char *string)
{
	int	i;

	i = 0;
	if (string[i] == '\'')
	{
		i++;
		while (string[i] && string[i] != '\'')
			i++;
	}
	return (i - 1);
}
