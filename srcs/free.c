/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 07:31:33 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/21 07:34:07 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <tools.h>

void	release_header(t_header **head, t_header *current)
{
	t_header	*tmp;
	t_header	*pointer;

	tmp = NULL;
	pointer = *head;
	while (pointer != current)
	{
		tmp = pointer;
		pointer = pointer->prev;
	}
	if (!tmp)
		*head = NULL;
	else
		tmp->prev = current->prev;
	munmap(current, current->size);
}

void	free(void *pointer)
{
	t_header	*header;
	t_block		*block;

}

