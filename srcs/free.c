/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 07:31:33 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/23 16:23:56 by tiboitel         ###   ########.fr       */
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
	t_header	*head;

	header = NULL;	
	block = NULL;
	pthread_mutex_lock(&(g_maps.mutex));
	if (pointer)
	{
		head = g_maps.tiny;
		// Find block by ptr information.
		while (head && !block)
		{
			if ((char *)pointer > (char *)head && (void *)pointer
				< (void *)head + head->size)
			{
				block = (t_block *)head + sizeof(t_header);
				while (block->pointer > pointer || pointer >= block->pointer +
					(size_t)block->size)
				{
					++block;
					if (!(block->size))
						// Le bon bloc est trouve le soustraire a l'hdr, signale qu'il est libre, si mon headr est vide le liberer sinon set le bloc suivant a 0.
						return ;
				}
			}
			head = head->prev;
		}

	}
	pthread_mutex_unlock(&(g_maps.mutex));
}

