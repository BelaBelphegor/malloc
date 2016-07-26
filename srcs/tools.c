/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 16:33:08 by tiboitel          #+#    #+#             */
/*   Updated: 2016/07/26 16:49:58 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tools.h>
#include <malloc.h>

static void			maps_current_block(t_header *header, void *pointer, 
		t_maps_enquiry *enquiry)
{
	t_block		*tmp;

	tmp = NULL;
	while (header && !tmp)
	{
		if ((char *)pointer > (char *)header && (void *)pointer <
			(void *)header + header->size)
		{
			tmp = (t_block *)header + sizeof(t_header);
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
	enquiry.pointer = NULL;
	if (pointer)
	{
		enquiry.head = &g_maps.tiny;
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
