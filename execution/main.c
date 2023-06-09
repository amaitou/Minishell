/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:54:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/09 23:54:46 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_dlist	*list;
	int		status;

	list = create_node();
	list->cmd = ft_strdup("/usr/bin/yes");
	list->args = ft_split("yes", ' ');
	list->builtin = _NONE;
	list->type = __PIPE;
	list->state = __D_QUOTES;
	append_node(&list, create_node());
	list->next->cmd = ft_strdup("/usr/bin/head");
	list->next->args = ft_split("head", ' ');
	list->next->builtin = _NONE;
	list->next->type = __NONE;
	list->next->state = __D_QUOTES;
	executor(list, &status, NULL);
}
