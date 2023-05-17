/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 06:25:50 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/17 07:52:36 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

	the only two things we know before creating a node are:
		- the content of the node is void pointer (this will allow us to store 
		any kind of data)
		- the next of this node is a pointer which points to NULL
	first of all, we have to allocate a memory for our new node using the malloc 
	function, and if allocation fails, "NULL" will be returned.
	after the allocation we assign the parameter of the function to the new 
	node's content meanwhile its next will be "NULL" (mostly it is the last node)

*/

#include "./superlib.h"

t_env	*ft_lstnew(void)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return ((void *)0);
	node->next = (void *)0;
	return (node);
}
