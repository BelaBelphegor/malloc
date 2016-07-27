/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 01:34:08 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/27 16:47:17 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_maps		g_maps = {NULL, NULL, NULL,
	PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER };

void			delete_memory_pool_block(t_block *block, size_t count)
{
	t_block		*tmp;

	while (block->size)
	{
		tmp = block + count;
		block->size = tmp->size;
		block->freed = tmp->freed;
		block->pointer = tmp->pointer;
		++block;
	}
}

size_t			get_memory_pool_size(t_block *block)
{
	size_t		size;

	size = 0;
	while (block->freed && block->size)
	{
		size += block->size;
		block++;
	}
	return (size);
}

t_block			*get_memory_pool_block(t_header *header, t_block *block, size_t size, 
		void *pointer)
{
	t_block		*tmp;
	size_t		freed;

	freed = block->size;
	tmp = block;
	while (freed < size)
	{
		++tmp;
		pointer = tmp->pointer;
		freed += tmp->size;
	}
	delete_memory_pool_block(block, ((void *)tmp - (void *)block) / sizeof(t_block));
	block->size = freed;
	block->freed = 0;
	block->pointer = pointer;
	header->used += block->size + sizeof(t_block);
	return (block);
}

static t_header	*header_create(t_header **head, size_t size)
{
	t_header	*tmp;
	t_header	*header;
	t_block		*block;
	size_t		page_size;

	tmp = *head;
	page_size = getpagesize();
	if (page_size <= SMALL)
		page_size *= 100;
	size = (((size + sizeof(t_block) * 2 + sizeof(t_header)) / page_size) + 1) * page_size + 1;
	if ((header = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) ==
		MAP_FAILED)
		return (NULL);
	*head = header;
	header->prev = tmp;
	header->size = size;
	header->used = sizeof(t_header) + sizeof(t_block);
	block = (void *)header + sizeof(t_header);
	block->size = 0;
	block->freed = 0;
	return (header);
}

int				header_check_integrity(t_header *header, size_t size)
{
	t_block		*block;
	size_t		free_size;

	free_size = header->size - sizeof(t_header) - sizeof(t_block);
	block = (t_block *)header + sizeof(t_header);
	while (block->size)
	{
		if (block->freed && block->size >= size)
			return (1);
		free_size -= block->size + sizeof(t_block);
		++block;
	}
	return (free_size >= size + sizeof(t_block));
}

static t_header	*header_request(t_header **head, size_t size)
{
	t_header	*header;

	header = *head;
	while (header && !(header->size - header->used >= size + sizeof(t_block))
		&& header_check_integrity(header, size))
		header = header->prev;
	if (!header)
		header = header_create(head, size);
	return (header);
}

static t_block	*block_create(t_header *head, size_t size)
{
	t_block		*block;
	t_block		*tmp;
	void		*pointer;

	// First block;
	block = (t_block *)((void *)head + sizeof(t_header));
	// Header end.
	pointer = (void *)head + head->size;
	while (block->size != 0)
	{
		pointer = block->pointer;
		if (get_memory_pool_size(block) >= size)
			return (get_memory_pool_block(head, block, size, pointer));
	}
	pointer -= size;
	block->size = size;
	block->freed = 0;
	block->pointer = pointer;
	head->used += size + sizeof(t_block);
	tmp = block + 1;
	tmp->size = 0;
	tmp->freed = 0;
	return (block);
}

static void		*claim_memory(t_header **head, size_t size)
{
	t_block		*block;
	t_header	*header;
	void		*pointer;

	header = NULL;
	block = NULL;
	pointer = NULL;
	if (!(header = header_request(head, size)))
		return (NULL);
	if (!(block = block_create(header, size)))
		return (NULL);
	pointer = block->pointer;
	return (pointer);
}

void			*malloc(size_t size)
{
	void		*pointer;
	
	if (!size)
		return (NULL);
	pthread_mutex_lock(&(g_maps.mutex));
	if (size <= TINY)
		pointer = claim_memory(&(g_maps.tiny), size);
	else if (size <= SMALL)
		pointer = claim_memory(&(g_maps.small), size);
	else
		pointer = claim_memory(&(g_maps.large), size);
	pthread_mutex_unlock(&(g_maps.mutex));
	show_alloc_mem();
	return (pointer);
}
