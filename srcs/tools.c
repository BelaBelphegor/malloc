/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 16:33:08 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/15 21:04:31 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tools.h>
#include <malloc.h>

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	size_t			i;

	if (src && dst)
	{
		i = 0;
		cdst = dst;
		csrc = (unsigned char *)src;
		while (i < n)
		{
			cdst[i] = csrc[i];
			++i;
		}
	}
	return (dst);
}

static void			maps_current_block(t_header *header, void *pointer,
		t_maps_enquiry *enquiry)
{
	t_block		*tmp;

	tmp = NULL;
	while (header && !tmp)
	{
		if ((char *)pointer > (char *)header && (void *)pointer <
				((void *)header + header->size))
		{
			tmp = (t_block *)((void *)header + sizeof(t_header));
			while (tmp->pointer > pointer || pointer >= tmp->pointer
					+ (size_t)tmp->size)
			{
				tmp++;
				if (!(tmp->size))
					return ;
			}
			enquiry->header = header;
			enquiry->block = tmp;
			enquiry->pointer = tmp->pointer;
		}
		header = header->prev;
	}
}

t_maps_enquiry		maps_enquiry(void *pointer)
{
	t_maps_enquiry	enquiry;

	enquiry.head = NULL;
	enquiry.block = NULL;
	enquiry.header = NULL;
	enquiry.pointer = pointer;
	if (pointer)
	{
		enquiry.head = &g_maps.tiny;
		maps_current_block(g_maps.tiny, pointer, &enquiry);
		if (!enquiry.block)
		{
			enquiry.head = &g_maps.small;
			maps_current_block(g_maps.small, pointer, &enquiry);
		}
		if (!enquiry.block)
		{
			enquiry.head = &g_maps.large;
			maps_current_block(g_maps.large, pointer, &enquiry);
		}
	}
	return (enquiry);
}
