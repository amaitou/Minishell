/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/03 12:06:42 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_spaces(char *s)
{
    while (*s && (*s == '\t' || *s == ' '))
        ++s;
    if (*s)
        return (0);
    return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_scanner	*scanner;
	t_prompt	*prompt;
    t_dlist     *head;
	// t_env		*env;

	(void)argc;
	(void)argv;
    head = NULL;
	// env = NULL;
	// env = init_env(env, envp);
	while (1)
	{
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		scanner = (t_scanner *)malloc(sizeof(t_scanner));
		scanner->command = prompt_string(prompt);
        if(!scanner->command)
        {
            free(prompt);
            free(scanner);
            exit(1);
        }
        if (check_spaces(scanner->command))
        {
            free(prompt);
            free(scanner);
            scanner->command = prompt_string(prompt);
        }
        if (ft_strlen(scanner->command))
        {
            command_scanner(head, scanner);
            add_history(scanner->command);
        }
        
	}
	return (0);
}
