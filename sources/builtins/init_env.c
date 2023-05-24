/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 07:05:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/24 22:42:42 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_v(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '=' && string[i])
		i++;
	return (i);
}

t_env	*init_env(t_env	*env, char **envp)
{
	int		i;
	t_env	*traveser;

	i = 0;
	env = ft_lstnew();
	traveser = env;
	while (envp[i])
	{
		traveser->key = ft_substr(envp[i], 0, get_v(envp[i]));
		traveser->value = ft_substr(envp[i],
				get_v(envp[i]) + 1, ft_strlen(envp[i]));
		if (envp[i + 1])
			ft_lstadd_back(&env, ft_lstnew());
		traveser = traveser->next;
		i++;
	}
	return (env);
}

// t_env	*init_env(t_env	*env, char **envp)
// {
// 	int		i;
// 	t_env	*head;
// 	t_env	*node;

// 	i = 0;
// 	(void)env;
// 	while (envp[i])
// 	{
// 		node = ft_lstnew();
// 		node->key = ft_substr(envp[i], 0, get_v(envp[i]));
// 		node->value = ft_substr(envp[i],
// 				get_v(envp[i]) + 1, ft_strlen(envp[i]));
// 		ft_lstadd_back(&head, node);
// 		i++;
// 	}
// 	return (head);
// }
