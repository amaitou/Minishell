/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:54:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/13 19:04:07 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_dlist	*list;
	int		status;

	// while (1)
	// {
		list = create_node();
		list->cmd = ft_strdup("/usr/bin/head");
		list->args = ft_split("head", ' ');
		list->builtin = _NONE;
		list->type = __PIPE;
		list->state = __D_QUOTES;
		append_node(&list, create_node());
		list->next->cmd = ft_strdup("/bin/ls");
		list->next->args = ft_split("ls", ' ');
		list->next->builtin = _NONE;
		list->next->type = __NONE;
		list->next->state = __D_QUOTES;
		// append_node(&list, create_node());
		// list->next->next->cmd = ft_strdup("/usr/bin/wc");
		// list->next->next->args = ft_split("wc -l", ' ');
		// list->next->next->builtin = _NONE;
		// list->next->next->type = __NONE;
		// list->next->next->state = __D_QUOTES;
		// append_node(&list, create_node());
		// list->next->next->next->cmd = ft_strdup("/usr/bin/wc");
		// list->next->next->next->args = ft_split("wc -l", ' ');
		// list->next->next->next->builtin = _NONE;
		// list->next->next->next->type = __NONE;
		// list->next->next->next->state = __D_QUOTES;
		executor(list, &status, NULL);
		free (list->next->next);
		free (list->next);
		free (list);
	// }
}
