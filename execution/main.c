/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:54:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 10:24:21 by bbouagou         ###   ########.fr       */
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
		list->cmd = ft_strdup("/bin/ls");
		list->args = ft_split("ls -la", ' ');
		list->type = __PIPE;
		// append_node(&list, create_node());
		// list->next->cmd = ft_strdup("/usr/bin/wc");
		// list->next->args = ft_split("wc -l", ' ');
		// list->next->type = __NONE;
		// append_node(&list, create_node());
		// list->next->next->cmd = ft_strdup("/usr/bin/wc");
		// list->next->next->args = ft_split("wc -l", ' ');
		// list->next->next->type = __NONE;
		// append_node(&list, create_node());
		// list->next->next->next->cmd = ft_strdup("/usr/bin/wc");
		// list->next->next->next->args = ft_split("wc -l", ' ');
		// list->next->next->next->type = __NONE;
		executor(list, &status, NULL);
		free (list->next->next);
		free (list->next);
		free (list);
	// }
}
