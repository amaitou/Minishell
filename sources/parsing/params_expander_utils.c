/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expander_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:42:37 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/18 11:24:19 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
