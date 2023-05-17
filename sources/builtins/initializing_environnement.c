/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_environnement.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 07:05:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/17 22:12:38 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	get_v(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '=' && string[i])
		i++;
	return (i);
}

t_env	*initialize_environnement(t_env	*env, char **envp)
{
	int		i;
	t_env	*traveser;

	i = 0;
	env = ft_lstnew();
	traveser = env;
	while (envp[i])
	{
		traveser->var_name = ft_substr(envp[i], 0, get_v(envp[i]));
		traveser->value = ft_substr(envp[i],
				get_v(envp[i]) + 1, ft_strlen(envp[i]));
		if (envp[i + 1])
			ft_lstadd_back(&env, ft_lstnew());
		traveser = traveser->next;
		i++;
	}
	return (env);
}
