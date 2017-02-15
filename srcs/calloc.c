/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 20:13:38 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/15 21:00:40 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "tools.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	pthread_mutex_lock(&(g_maps.mutex_free));
	if (size > 0 && count > (~(size_t)0) / size)
		return (NULL);
	size = count * size;
	ptr = malloc(size);
	i = -1;
	while (++i < size)
		*((unsigned char *)(ptr + i)) = 0;
	pthread_mutex_unlock(&(g_maps.mutex_free));
	return (ptr);
}
