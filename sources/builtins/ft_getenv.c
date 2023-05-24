/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:15:28 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/24 19:32:31 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *string, t_env *env)
{
	t_env	*traverser;

	traverser = env;
	while (traverser)
	{
		if (!ft_strcmp(string, traverser->key))
			return (traverser->value);
		traverser = traverser->next;
	}
	return (NULL);
}
