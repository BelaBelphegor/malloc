/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 07:31:33 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/26 16:49:36 by tiboitel         ###   ########.fr       */
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
	t_header			*header;
	t_block				*block;
	t_maps_enquiry		enquiry;
	
	header = NULL;	
	block = NULL;
	pthread_mutex_lock(&(g_maps.mutex));
	if (pointer)
	{
		enquiry = maps_enquiry(pointer);
		block = enquiry.block;
		header = enquiry.header;
		if (block && block->freed == 0 && block->pointer == pointer)
		{
			header->used -= block->size + sizeof(t_block);
			block->freed = 1;
			if (header->used == sizeof(t_header) + sizeof(t_block))
				release_header(enquiry.head, enquiry.header);
			else if ((block + 1)->size == 0)
			{
				block->size = 0;
				block->freed = 0;
			}
		}
	}
	pthread_mutex_unlock(&(g_maps.mutex));
}

