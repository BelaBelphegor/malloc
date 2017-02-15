/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 18:26:56 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/15 22:31:33 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "tools.h"

void	*realloc(void *ptr, size_t size)
{
	t_block			*tmp;
	t_maps_enquiry	enquiry;
	void			*allocation;

	pthread_mutex_lock(&(g_maps.mutex_realloc));
	enquiry = maps_enquiry(ptr);
	tmp = enquiry.block;
	allocation = NULL;
	if (!tmp || (tmp && tmp->size <= size))
		allocation = malloc(size);
	if (allocation && ptr && tmp)
	{
		ft_memcpy(allocation, ptr, tmp->size);
		free(ptr);
	}
	pthread_mutex_unlock(&(g_maps.mutex_realloc));
	return (allocation);
}
