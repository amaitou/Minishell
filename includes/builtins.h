/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 07:06:21 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/17 07:14:32 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./minishell.h"

typedef struct s_env
{
	char			*var_name;
	char			*value;
	struct s_env	*next;
}	t_env;

void	initialize_environnement(t_env *env, char **envp);

#endif