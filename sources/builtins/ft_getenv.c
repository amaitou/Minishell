/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:15:28 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/17 22:23:18 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char	*ft_getenv(char *string, t_env *env)
{
	t_env	*traverser;

	traverser = env;
	while (traverser)
	{
		if (!ft_strcmp(string, traverser->var_name))
			return (traverser->value);
		traverser = traverser->next;
	}
	return (NULL);
}
