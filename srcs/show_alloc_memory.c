/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 14:31:55 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/13 18:21:24 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <tools.h>

static size_t		show_memory_area(const char *area, t_header *current)
{
	t_block		*block;
	t_block		*first;
	size_t		size;

	size = 0;
	ft_putstr(area);
	ft_putpointer(current);
	ft_putstr("\n");
	block = (t_block *)((void *)(current) + sizeof(t_header));
	first = block;
	while (block->size)
		block++;
	while (block != first)
	{
		block--;
		ft_putpointer(block->pointer);
		ft_putstr(" - ");
		ft_putpointer(block->pointer + block->size);
		ft_putstr(" : ");
		ft_putnbr(block->size);
		ft_putstr(" octets\n");
		size += block->size;
	}
	return (size);
}

void		show_alloc_mem(void)
{
	t_header	*header;
	size_t		size;
	
	size = 0;
	pthread_mutex_lock(&(g_maps.mutex_free));
	header = g_maps.tiny;
	while (header)
	{
		size += show_memory_area("TINY : ", header);
		header = header->prev;
	}
	header = g_maps.small;
	while (header)
	{
		size += show_memory_area("SMALL : ", header);
		header = header->prev;
	}
	header = g_maps.large;
	while (header)
	{
		size += show_memory_area("LARGE : ", header);
		header = header->prev;
	}
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
	pthread_mutex_unlock(&(g_maps.mutex_free));
}
